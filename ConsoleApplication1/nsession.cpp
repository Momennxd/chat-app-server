#include "nsession.h"
#include "network_layer.h"   
#include "DEF_CORE.h"        
#include "parser.h"        
#include "tcp_server.h"        
#include "router.h"        
#include "router_manager.h"

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
    // ensure object stays alive while we clean up
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

    // remove from network layer (safe: self keeps object alive)
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

    asio::async_read(
        m_socket,
        asio::buffer(&m_msg_length, sizeof(m_msg_length)),
        [this, self](const error_code& ec, std::size_t) {
            if (ec) {
                _abort();
                return;
            }

            m_msg_length = ntohl(m_msg_length);

            if (m_msg_length == 0 || m_msg_length > MAX_MESSAGE_SIZE) {
                _abort();
                return;
            }

            m_body_buffer.resize(m_msg_length);
            _read_body();
        });
}

void nsession::_read_body() {
    auto self = shared_from_this();

    asio::async_read(
        m_socket,
        asio::buffer(m_body_buffer.data(), m_msg_length),
        [this, self](const error_code& ec, std::size_t) {
            if (ec) {
                _abort();
                return;
            }

            _touch();

            std::shared_ptr<request> req;
            try {
                req = parser::parse(m_body_buffer);
            }
            catch (const std::exception& ex) {
                std::cerr << "Parse error: " << ex.what() << "\n";
                _abort();
                return;
            }

            if (req) {

                auto _router = router_manager::get_router();

                if (_router) {
                    try {
                        auto resp = _router->rout(req);
                    }
                    catch (const std::exception& ex) {
                        std::cerr << "Router error: " << ex.what() << "\n";
                        _abort();
                        return;
                    }
                }
                else {
                    std::cerr << "Router not initialized\n";
                }
            }

            // ready for next message
            _read_header();
        });
}
