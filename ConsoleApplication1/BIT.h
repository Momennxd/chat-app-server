#pragma once
#include <iostream>
using namespace std;
static class BIT
{
public:
    static inline uint32_t bytes_to_uint32(const uint8_t* start) {
        return
            (uint32_t(start[0]) << 24) |
            (uint32_t(start[1]) << 16) |
            (uint32_t(start[2]) << 8) |
            uint32_t(start[3]);
        
    }

    static inline std::vector<uint8_t> uint32_to_bytes_buffer(uint32_t num) noexcept {
        std::vector<uint8_t> buffer;
        buffer.reserve(4);
        buffer.push_back(static_cast<uint8_t>((num >> 24) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((num >> 16) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((num >> 8) & 0xFF));
        buffer.push_back(static_cast<uint8_t>(num & 0xFF));
        return buffer;
    }



    static inline uint32_t bytes_to_uint8(const uint8_t* byte) {
        return uint32_t(byte[0]);
    }


    static inline string bytes_to_string(const uint8_t* byte, size_t length) {
        if (byte == nullptr || length <= 0) return "";
        string res = "";
        int i = 0;
        for (byte; byte != nullptr && i < length; byte++) {
            res += *byte; i++;
        }
        return res;
    }

};

