

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
	typed_response<uint32_t> add_session(tcp::socket&& socket) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		++this->_sessions_count;
		auto new_session = std::make_shared<session>(std::move(socket), _sessions_count);

		_sessions.emplace(_sessions_count, new_session);


		//returns the added session id
		return typed_response<uint32_t>(OK, _sessions_count);
	}

	typed_response<uint32_t> remove_session(uint32_t session_id) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		if (!this->_sessions.count(session_id)) return typed_response<uint32_t>(SESSION_NOT_EXIST_IN_DB, 0);
		this->_sessions.erase(session_id);
		return typed_response<uint32_t>(OK, 0);
	}

	typed_response<shared_ptr<const session>> get_session(uint32_t session_id) override
	{
		std::lock_guard<std::mutex> lock(_gLock);
		auto it = this->_sessions.find(session_id);
		if (it == this->_sessions.end()) return typed_response<shared_ptr<const session>>(SESSION_NOT_EXIST_IN_DB, nullptr);
		return typed_response<shared_ptr<const session>>(OK, it->second);
	}

	typed_response<size_t> get_sessions_size() {
		std::lock_guard<std::mutex> lock(_gLock);
		return typed_response<size_t>(OK, _sessions.size());
	}
};

