#pragma once
#include <asio.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include "DEF_CORE.h"
#include "message.h"


using namespace std;
using namespace asio;
using namespace asio::ip;


class session : public enable_shared_from_this<session>
{

private:

	tcp::socket m_socket;
	std::chrono::system_clock::time_point m_last_active;
	queue<vector<uint8_t>> m_messages;
	int m_id;
	string m_name;

	void _do_write_async();
	 void _abort();

public:

	int getid() const;
	void set_id(const int id);

	string get_name() const;
	void set_name(const string& name);

	void touch();
	int get_idle_time();

	session(tcp::socket&& socket, int id);

	void socket_write_async(const vector<uint8_t>& buffer);

	void close();

	bool is_active();

	~session();

};

