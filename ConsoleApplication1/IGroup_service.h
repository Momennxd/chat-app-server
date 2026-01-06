#pragma once
#include "DEF_CORE.h"
#include "session.h"
#include "IGroup_repo.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

class IGroup_service
{
public:
	virtual ~IGroup_service() = default;
	virtual typed_response<uint32_t> add_group() = 0;
	virtual typed_response<uint32_t> connect_to_group(uint32_t group_id,  shared_ptr<session> session_ptr) = 0;
	virtual typed_response<uint32_t> disconnect_from_group(uint32_t group_id,  shared_ptr<session> session_ptr) = 0;
	virtual typed_response<unordered_set<shared_ptr<session>>> get_group_sessions( uint32_t group_id) = 0;
};

