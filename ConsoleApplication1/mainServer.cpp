#include <asio.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include "message.h"
#include "IGroup_service.h"
#include "Group_service.cpp"
#include "IGroup_repo.h"
#include "Group_repo.cpp"

#include "ISession_service.h"
#include "session_service.cpp"
#include "ISession_repo.h"
#include "session_repo.cpp"


using namespace std;
using namespace asio;
using namespace asio::ip;

//1. What is a strand in ASIO ?
//
//A strand is a mechanism in ASIO that guarantees that handlers(callbacks) do not execute concurrently.
//
//Even if your io_context has multiple threads running(io_context.run() in multiple threads), a strand ensures that the code inside its handlers runs one at a time, in order.
//
//This is extremely useful for serializing access to shared data, like your m_messages queue.

vector<shared_ptr<tcp::socket>> clients;
int n = 0;

void StartAccepting(io_context& io, tcp::acceptor& acceptor, vector<shared_ptr<tcp::socket>>& clients) {

    auto socket = make_shared<tcp::socket>(io);
    acceptor.async_accept(*socket, [&, socket](const asio::error_code& ec) {
        if (!ec) {
            n++;
            cout << "A client connected: " << n << endl;

            clients.push_back(socket);

            message msg("momen", 1, "hi");
            auto msg_buffer = msg.serialize();
          
            asio::async_write(*socket, asio::buffer(msg_buffer),
                [socket](const asio::error_code& ec, size_t bytes_sent) {
                    if (!ec) {
                        cout << "Sent message to client\n";
                    }
                    else {
                        cout << "Write failed: " << ec.message() << endl;
                    }
                });
        }
        else {
            cout << "Accept failed: " << ec.message() << endl;
        }
        StartAccepting(io, acceptor, clients);
        });
}

int main() {

   /* io_context io;

    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1234));
    cout << "Server running...\n";

    StartAccepting(io, acceptor, clients);
  
    io.run();*/


  

    
    return 0;
}
