// main.cpp
#include <asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <csignal>

#include "group_repo.h"
#include "session_repo.h"
#include "group_service.h"
#include "session_service.h"
#include "messenger_service.h"
#include "tcp_server.h"
#include "services_manager.h"




int main() {
    try {
        asio::io_context io;

        auto groupRepo = std::make_shared<group_repo>();
        auto sessionRepo = std::make_shared<session_repo>();

        auto gs = std::make_shared<group_service>(groupRepo);      
        auto ss = std::make_shared<session_service>(sessionRepo);   
        auto ms = std::make_shared<messenger_service>(gs);    
        services_manager::initialize(gs, ss, ms);
        
        const std::string ipStr = "127.0.0.1";
        asio::ip::address address = asio::ip::make_address(ipStr);

        gs->add_group(); // create default group with id 1

        unsigned short port = 8080;
       // tcp_server server(io, port, gs, ss, ms);
        tcp_server server(io, address, port, gs, ss, ms);
        server.start();

        io.run();

    }
    catch (const std::exception& ex) {
        std::cerr << "Fatal exception: " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
