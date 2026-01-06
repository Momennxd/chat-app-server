#include "IGroup_service.h"

class group_service : public IGroup_service
{
private:

	shared_ptr<IGroup_repo> _gc;

public:

	group_service(shared_ptr<IGroup_repo> gc) {
		this->_gc = gc;
	}

	typed_response<uint32_t> add_group() {
		return _gc->add_group();
	}
	typed_response<uint32_t> connect_to_group(uint32_t group_id,  shared_ptr<session> session_ptr) override {
		return this->_gc->connect_to_group(group_id, session_ptr);
	}
	typed_response<uint32_t> disconnect_from_group(uint32_t group_id, shared_ptr<session> session_ptr) override {
		return this->_gc->disconnect_from_group(group_id, session_ptr);
	}
	typed_response<unordered_set<shared_ptr<session>>> get_group_sessions(uint32_t group_id) override {
		return this->_gc->get_group_sessions(group_id);
	}
};

