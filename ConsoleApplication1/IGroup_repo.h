#pragma once
#include "DEF_CORE.h"
#include "session.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

class IGroup_repo
{
public:
	virtual ~IGroup_repo() = default;
	virtual int add_group() = 0;
	virtual void connect_to_group(const int group_id, const shared_ptr<session> session_ptr) = 0;
	virtual void disconnect_from_group(const int group_id, const shared_ptr<session> session_ptr) = 0;
	virtual const unordered_set<shared_ptr<session>>& get_group_sessions(const int group_id) = 0;
};

