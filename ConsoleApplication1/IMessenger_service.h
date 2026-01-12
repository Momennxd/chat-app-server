// IMessenger_service.h
#pragma once

#include "response.h"   // for typed_response<T>
#include <vector>
#include <cstdint>

class IMessenger_service {
public:
    virtual ~IMessenger_service() = default;
    virtual typed_response<uint32_t> send_message(const std::vector<uint8_t>& msg_buffer, uint32_t group_id) = 0;
};
