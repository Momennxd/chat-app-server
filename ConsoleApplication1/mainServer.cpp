
#include <asio.hpp>
#include <iostream>
//#include <vector>
//#include <queue>
//#include "message.h"
//#include "router.h"
//#include "DEF_CORE.h"
//#include "BIT.h"
//#include "tcp_server.h"
//#include "group_service.h"
//#include "session_service.h"
//#include "messenger_service.h"
//#include "ISession_repo.h"
//#include "IGroup_repo.h"

using namespace std;
using namespace asio;



/*Think of TCP as giving you:

✅ Reliable delivery — no lost bytes
✅ Ordered bytes — exactly what you sent, in order
✅ Flow control — protects receiver
✅ Congestion control — plays nicely on the network

But it does not give you:
❌ Message boundaries — that’s up to you
❌ Encryption — you add TLS/SSL for that
❌ Broadcast/multicast — one-to-many isn’t supported natively

*/




//1. What is a strand in ASIO ?
//
//A strand is a mechanism in ASIO that guarantees that handlers(callbacks) do not execute concurrently.
//
//Even if your io_context has multiple threads running(io_context.run() in multiple threads), a strand ensures that the code inside its handlers runs one at a time, in order.
//
//This is extremely useful for serializing access to shared data, like your m_messages queue.





int main() {

    //try {
    //    // Create io_context (caller owns it)
    //    asio::io_context io;


    //    auto group_repo = std::make_shared<IGroup_repo>();
    //    auto session_repo = std::make_shared<ISession_repo>();

    //    // Create services
    //    auto gs = std::make_shared<group_service>(group_repo);
    //    auto ss = std::make_shared<session_service>(session_repo);
    //    auto ms = std::make_shared<messenger_service>(group_repo, session_repo);

    //    // Create and start server
    //    tcp_server server(io, 8080, gs, ss, ms);

    //    server.start();


    //    // ========== IMPORTANT: must run io_context! ==========
    //    // Option 1: Run in main thread (blocks until stopped)
    //    std::cout << "Running io_context in main thread...\n";
    //    io.run();
    //    // =========================================================

    //}
    //catch (const std::exception& e) {
    //    std::cerr << "Exception: " << e.what() << "\n";
    //    return 1;
    //}

    return 0;
}