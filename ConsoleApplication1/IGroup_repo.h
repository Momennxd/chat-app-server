// IGroup_repo.h
#pragma once
#include <unordered_set>
#include "response.h"

class IGroup_repo {
public:
    virtual ~IGroup_repo() = default;
    virtual typed_response<uint32_t> add_group() = 0;
    virtual typed_response<uint32_t> connect_to_group(uint32_t group_id, uint32_t session_id) = 0;
    virtual typed_response<uint32_t> disconnect_from_group(uint32_t group_id, uint32_t session_id) = 0;
    virtual typed_response<std::unordered_set<uint32_t>> get_group_sessions(uint32_t group_id) = 0;
};
