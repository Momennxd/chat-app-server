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

	unordered_map<int, unordered_set<shared_ptr<session>>> _group_chats;
	int groups_count;
	mutex _gLock;


public:

	group_repo() {
		groups_count = 0;
	}

	int add_group()
	{
		std::lock_guard<std::mutex> lock(_gLock);
		++this->groups_count;
		this->_group_chats[groups_count] = {};
		return this->groups_count;
	}

	void connect_to_group(const int group_id, const shared_ptr<session> session_ptr)
	{
		std::lock_guard<std::mutex> lock(_gLock);
		if (!this->_group_chats.count(group_id)) return;
		this->_group_chats[group_id].insert(session_ptr);
	}

	void disconnect_from_group(const int group_id, const shared_ptr<session> session_ptr)
	{
		std::lock_guard<std::mutex> lock(_gLock);
		if (this->_group_chats.count(group_id))
			this->_group_chats[group_id].erase(session_ptr);
	}

	const unordered_set<shared_ptr<session>>& get_group_sessions(const int group_id)
	{
		std::lock_guard<std::mutex> lock(_gLock);
		auto it = this->_group_chats.find(group_id);
		if (it == _group_chats.end()) return {};
		return it->second;
	}
};

