#pragma once
#include <asio.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include "response.h"
#include "DEF_CORE.h"

using namespace std;
using namespace asio;
using namespace asio::ip;


class session : public enable_shared_from_this<session>
{

private:

	std::chrono::system_clock::time_point m_last_active;
	int m_id;
	string m_name;


public:

	int getid() const;
	void set_id(const int id);

	string get_name() const;
	void set_name(const string& name);

	void touch();
	int get_idle_time();

	session(int id);

	void start();

	~session();

};

