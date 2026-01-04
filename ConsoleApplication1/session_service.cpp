#pragma once
#include "DEF_CORE.h"
#include "message.h"
#include "session.h"
#include "ISession_repo.h"
#include "ISession_service.h"
#include <asio.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

class session_service : public ISession_service
{
private:

	shared_ptr<ISession_repo> _sp;

public:

	session_service(shared_ptr<ISession_repo> sp) : _sp(sp) {}


	int add_session(tcp::socket&& socket) override {
		return _sp->add_session(move(socket));
	}
	void remove_session(int session_id) override {
		this->_sp->remove_session(session_id);
	}
	const shared_ptr<session> get_session(int session_id) override {
		return this->_sp->get_session(session_id);
	}
};

