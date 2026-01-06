#pragma once
#include "DEF_CORE.h"
#include "session.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include "IGroup_repo.h"

class group_repo : public IGroup_repo
{
private:

	unordered_map<uint32_t, unordered_set<shared_ptr<session>>> _group_chats;
	uint32_t groups_count;
	mutex _gLock;


public:

	group_repo() {
		groups_count = 0;
	}

	typed_response<uint32_t> add_group() override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		++this->groups_count;
		this->_group_chats[groups_count] = {};
		return typed_response<uint32_t>(OK, this->groups_count);
	}

	typed_response<uint32_t> connect_to_group(const uint32_t group_id, const shared_ptr<session> session_ptr) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		if (!this->_group_chats.count(group_id)) return typed_response<uint32_t>(GROUP_NOT_EXIST, 0);
		this->_group_chats[group_id].insert(session_ptr);
		return typed_response<uint32_t>(OK, 0);
	}

	typed_response<uint32_t> disconnect_from_group(const uint32_t group_id, const shared_ptr<session> session_ptr) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		if (this->_group_chats.count(group_id)) { 
			this->_group_chats[group_id].erase(session_ptr);
			return typed_response<uint32_t>(OK, 0);
		}
		return typed_response<uint32_t>(GROUP_NOT_EXIST, 0);
	}

	typed_response<unordered_set<shared_ptr<session>>> get_group_sessions(const uint32_t group_id) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		auto it = this->_group_chats.find(group_id);
		if (it == _group_chats.end()) return typed_response<unordered_set<shared_ptr<session>>>(GROUP_NOT_EXIST, {});
		return typed_response<unordered_set<shared_ptr<session>>>(OK, it->second);
	}
};

