#pragma once
#include "DEF_CORE.h"
#include "message.h"
#include "session.h"
#include "response.h"
#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "ISession_repo.h"
#include <mutex>

class ISession_repo
{
public:

	virtual ~ISession_repo() = default;
	virtual typed_response<uint32_t> add_session(tcp::socket&& socket) = 0;
	virtual typed_response<uint32_t> remove_session(uint32_t session_id) = 0;
	virtual typed_response<shared_ptr<const session>> get_session(uint32_t session_id) = 0;
};