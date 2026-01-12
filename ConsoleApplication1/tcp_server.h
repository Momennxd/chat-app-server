#pragma once

#include <asio.hpp>
#include <atomic>
#include <memory>
#include "router.h"

class IGroup_service;
class ISession_service;
class IMessenger_service;

class tcp_server
{
public:
    tcp_server(
        asio::io_context& ctx,
        const asio::ip::address& address,
        unsigned short port,
        std::shared_ptr<IGroup_service> gs,
        std::shared_ptr<ISession_service> ss,
        std::shared_ptr<IMessenger_service> ms
    );

    void start();
    void stop();

    ~tcp_server();


private:
    void _accept_next();

private:
    std::atomic<bool> is_on_{ false };
    asio::io_context& io_context_;
    asio::ip::tcp::acceptor acceptor_;

    std::shared_ptr<IGroup_service> _gs;
    std::shared_ptr<ISession_service> _ss;
    std::shared_ptr<IMessenger_service> _ms;

};
