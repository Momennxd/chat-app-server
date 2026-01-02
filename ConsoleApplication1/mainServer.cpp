#include <asio.hpp>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using namespace asio;
using namespace asio::ip;

vector<shared_ptr<tcp::socket>> clients;
int n = 0;

void StartAccepting(io_context& io, tcp::acceptor& acceptor, vector<shared_ptr<tcp::socket>>& clients) {

    auto socket = make_shared<tcp::socket>(io);
    acceptor.async_accept(*socket, [&, socket](const asio::error_code& ec) {
        if (!ec) {
            n++;
            cout << "A client connected: " << n << endl;

            clients.push_back(socket);

            // send message with newline
            string msg = "hi there\n";
          
            asio::async_write(*socket, asio::buffer(msg),
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
    io_context io;

    tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 1234));
    cout << "Server running...\n";

    StartAccepting(io, acceptor, clients);
  
    io.run();
    return 0;
}
