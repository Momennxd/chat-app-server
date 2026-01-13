#include "nsession.h"
#include "network_layer.h"   
#include "DEF_CORE.h"        
#include "parser.h"        
#include "tcp_server.h"        
#include "router.h"        
#include "router_manager.h"
#include "response.h"

#include <asio.hpp>
#include <iostream>

using asio::error_code;



// ---------------- ctor / dtor ----------------

nsession::nsession(tcp::socket&& socket, uint32_t id)
    : m_socket(std::move(socket)), m_id(id)
{
    _touch();
}

nsession::~nsession()
{
    _abort();
}

// ---------------- public API ----------------

void nsession::start()
{
    _read_header();
}

void nsession::close()
{
    _abort();
}

bool nsession::is_active() const
{
    return m_socket.is_open();
}

uint32_t nsession::getid() const
{
    return m_id;
}

void nsession::socket_write_async(const std::vector<uint8_t>& buffer)
{
    if (!is_active()) return;

    _touch();

    m_outbox.push(buffer);

    // if another write is already in progress, do nothing
    if (m_outbox.size() > 1)
        return;

    _do_write_async();
}



// ---------------- internal helpers ----------------

void nsession::_touch()
{
    m_last_active = std::chrono::system_clock::now();
}



void nsession::_abort()
{
    std::shared_ptr<nsession> self;
    try {
        self = shared_from_this();
    }
    catch (...) {}

    error_code ec;

    if (m_socket.is_open()) {
        m_socket.cancel(ec);
        m_socket.shutdown(tcp::socket::shutdown_both, ec);
        m_socket.close(ec);
    }

    while (!m_outbox.empty())
        m_outbox.pop();

    network_layer::remove_session(m_id);
}







// ---------------- async write ----------------

void nsession::_do_write_async()
{
    if (!is_active() || m_outbox.empty())
        return;
    auto self = shared_from_this();
    const auto& msg = m_outbox.front();

    asio::async_write(
        m_socket,
        asio::buffer(msg),
        [self](const error_code& ec, std::size_t /*bytes*/) {
            if (ec) {
                self->_abort();
                return;
            }

            self->m_outbox.pop();

            if (!self->m_outbox.empty())
                self->_do_write_async();
        });
}



// ---------------- async read ----------------

void nsession::_read_header()
{
    auto self = shared_from_this();

    // read exactly 4 bytes of header into m_header_bytes (header bytes is the length of the msg body in bytes decoded and coded in big endian)
    asio::async_read(
        m_socket,
        asio::buffer(m_header_bytes),
        [self](const asio::error_code& ec, std::size_t /*bytes_transferred*/) {
            if (ec) {
                self->_abort();
                return;
            }

            // decode big-endian length from the 4 header bytes
            uint32_t len = BIT::bytes_to_uint32(self->m_header_bytes.data());

       
            if (len == 0 || len > MAX_MESSAGE_SIZE) {
                std::cerr << "Invalid length: " << len << "\n";
                self->_abort();
                return;
            }

            self->m_msg_length = len;
            self->m_body_buffer.resize(self->m_msg_length);

            self->_read_body();
        });
}

void nsession::_read_body()
{
    auto self = shared_from_this();

    // read exactly m_msg_length bytes into the body buffer
    asio::async_read(
        m_socket,
        asio::buffer(self->m_body_buffer.data(), self->m_msg_length),
        [self](const asio::error_code& ec, std::size_t /*bytes_transferred*/) {
            if (ec) {
                self->_abort();
                return;
            }

            self->_touch();

            try {
                auto req = parser::parse(self->m_body_buffer);
                if (req) {
                    auto _router = router_manager::get_router();
                    if (_router) {
                        auto resp = _router->rout(req);
                        
                        if (resp) {
                            auto typ_resp = dynamic_pointer_cast<typed_response<uint32_t>>(resp);
                            
                            // TODOOO =>>> handle resp 
                        }
                      
                    }
                    else {
                        std::cerr << "Router not initialized\n";
                    }
                }
            }
            catch (const std::exception& ex) {
                std::cerr << "Parse/router error: " << ex.what() << "\n";
                self->_abort();
                return;
            }

            // ready for next message
            self->_read_header();
        });
}
