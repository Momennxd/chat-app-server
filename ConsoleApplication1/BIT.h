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


	

};

