#pragma once

#include <asio.hpp>
#include <chrono>
#include <cstdint>
#include <queue>
#include <vector>
#include <memory>

class nsession : public std::enable_shared_from_this<nsession>
{
public:
    using tcp = asio::ip::tcp;

    explicit nsession(tcp::socket&& socket, uint32_t id);
    ~nsession();

    void start();
    void close();

    void socket_write_async(const std::vector<uint8_t>& buffer);

    bool is_active() const;
    uint32_t getid() const;

private:
    tcp::socket m_socket;

    uint32_t m_id;

    std::chrono::system_clock::time_point m_last_active;

    // outbound messages (ordered)
    std::queue<std::vector<uint8_t>> m_outbox;

    // inbound message handling
    uint32_t m_msg_length = 0;
    std::vector<uint8_t> m_body_buffer;

private:

    void _touch();
    void _abort();

    void _read_header();
    void _read_body();

    void _do_write_async();
};
