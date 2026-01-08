#pragma once
#include <iostream>
using namespace std;
static class BIT
{
public:
    static inline uint32_t bytes_to_uint32(const uint8_t* start) {
        return
            (uint32_t(start[3]) << 24) |
            (uint32_t(start[2]) << 16) |
            (uint32_t(start[1]) << 8) |
            uint32_t(start[0]);
        
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

