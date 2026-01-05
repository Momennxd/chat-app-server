#pragma once
#include "DEF_CORE.h"
#include "message.h"
#include "session.h"
#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>


class ISession_service
{
public:
	virtual ~ISession_service() = default;
	virtual uint32_t add_session(tcp::socket&& socket) = 0;
	virtual void remove_session(uint32_t session_id) = 0;
	virtual shared_ptr<const session> get_session(uint32_t session_id) = 0;
};

