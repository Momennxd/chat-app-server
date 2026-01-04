#pragma once
#include "DEF_CORE.h"
#include "message.h"
#include "session.h"
#include "ISession_repo.h"
#include <asio.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <mutex>

class session_repo : public ISession_repo
{
private:
	unordered_map<int, shared_ptr<session>> _sessions;
	int _sessions_count;
	mutex _gLock;

public:

	session_repo() {
		_sessions_count = 0;
	}
	int add_session(tcp::socket&& socket) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		++this->_sessions_count;

		auto s_ptr = std::make_shared<session>(std::move(socket), _sessions_count);
		_sessions.emplace(_sessions_count, s_ptr);

		return _sessions_count;
	}

	void remove_session(int session_id) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		this->_sessions.erase(session_id);
	}

	const shared_ptr<session> get_session(int session_id) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		auto it = this->_sessions.find(session_id);
		if (it == this->_sessions.end()) return nullptr;
		return it->second;
	}

	int get_sessions_size() {
		std::lock_guard<std::mutex> lock(_gLock);
		return _sessions.size();
	}
};

