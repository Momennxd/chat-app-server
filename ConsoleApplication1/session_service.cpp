

class session_service : public ISession_service
{
private:

	shared_ptr<ISession_repo> _sp;

public:

	session_service(shared_ptr<ISession_repo> sp) : _sp(sp) {}

	typed_response<uint32_t> add_session(tcp::socket&& socket) override {
		return _sp->add_session(move(socket));
	}
	typed_response<uint32_t> remove_session(uint32_t session_id) override {
		return this->_sp->remove_session(session_id);
	}
	typed_response<shared_ptr<const session>> get_session(uint32_t session_id) override {
		return this->_sp->get_session(session_id);
	}
};

