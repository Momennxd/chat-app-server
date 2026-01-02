#pragma once
#include <asio.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include "DEF_CORE.h"
#include "message.h"
#include "session.h"

using namespace std;
using namespace asio;
using namespace asio::ip;

class group_chat
{
private:

	unordered_map<int, session*> m_sessions;
	int m_id;

public:

	int getid();
	void set_id(const int id);

	size_t get_sessions_count();

	session* get_session(int id);
	bool add_session(session* s);
	bool remove_session(int id);
	void send_message_to_all_async(message& msg);

};

