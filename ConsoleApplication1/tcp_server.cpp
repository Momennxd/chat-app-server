#include "tcp_server.h"

#include "nsession.h"
#include "network_layer.h"
#include "IGroup_service.h"
#include "ISession_service.h"
#include "IMessenger_service.h"
#include "router_manager.h"
#include "BIT.h"


#include <iostream>


using asio::ip::tcp;



tcp_server::tcp_server(
    asio::io_context& ctx,
    const asio::ip::address& address,
    unsigned short port,
    std::shared_ptr<IGroup_service> gs,
    std::shared_ptr<ISession_service> ss,
    std::shared_ptr<IMessenger_service> ms
)
    : io_context_(ctx),
    acceptor_(ctx, tcp::endpoint(address, port)),
    _gs(std::move(gs)),
    _ss(std::move(ss)),
    _ms(std::move(ms))
{
    auto r = std::make_shared<router>(_gs, _ss, _ms);
    router_manager::initialize(r);
}

void tcp_server::start()
{
    if (is_on_.exchange(true))
        return;

    _accept_next();

    std::cout << "Server started on port "
        << acceptor_.local_endpoint().port() << "\n";
}

void tcp_server::stop()
{
    if (!is_on_.exchange(false))
        return;

    std::cout << "Stopping server...\n";
    acceptor_.cancel();
    std::cout << "Server stopped\n";
}

tcp_server::~tcp_server()
{
    stop();
}

void tcp_server::_accept_next()
{
    if (!is_on_.load())
        return;

    acceptor_.async_accept(
        [this](std::error_code ec, tcp::socket socket)
        {
            if (!ec && is_on_.load())
            {
                try
                {
                    auto resp = _ss->add_session();
                    if (resp.status() != OK)
                        throw std::runtime_error("Failed to create session ID");

                    uint32_t session_id = resp.value();
                    auto ns_ptr = std::make_shared<nsession>(
                        std::move(socket),
                        session_id
                    );

                    network_layer::add_session(session_id, ns_ptr);

					// send session ID to client
                    auto buf = BIT::uint32_to_bytes_buffer(session_id);
                    ns_ptr->socket_write_async(buf);


					//start the session to read messages in async mode
                    ns_ptr->start();
                }
                catch (const std::exception& e)
                {
                    std::cerr << "Accept handling failed: "
                        << e.what() << "\n";
                }
            }
            else if (ec && ec != asio::error::operation_aborted)
            {
                std::cerr << "Accept error: " << ec.message() << "\n";
            }

            if (is_on_.load())
                _accept_next();
        }
    );
}
