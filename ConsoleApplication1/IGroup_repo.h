#pragma once
#include "DEF_CORE.h"
#include "session.h"
#include "response.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

class IGroup_repo
{
public:
	virtual ~IGroup_repo() = default;
	virtual typed_response<uint32_t> add_group() = 0;
	virtual typed_response<uint32_t> connect_to_group(const uint32_t group_id, const shared_ptr<session> session_ptr) = 0;
	virtual typed_response<uint32_t> disconnect_from_group(const uint32_t group_id, const shared_ptr<session> session_ptr) = 0;
	virtual typed_response<unordered_set<shared_ptr<session>>> get_group_sessions(uint32_t group_id) = 0;
};

