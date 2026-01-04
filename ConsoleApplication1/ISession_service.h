#pragma once
#include "DEF_CORE.h"
#include "message.h"
#include "session.h"
#include <asio.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>


class ISession_service
{
public:
	virtual ~ISession_service() = default;
	virtual int add_session(tcp::socket&& socket) = 0;
	virtual void remove_session(int session_id) = 0;
	virtual const shared_ptr<session> get_session(int session_id) = 0;
};

