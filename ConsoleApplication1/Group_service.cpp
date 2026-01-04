#include "IGroup_service.h"

class group_service : public IGroup_service
{
private:

	shared_ptr<IGroup_repo> _gc;

public:

	group_service(shared_ptr<IGroup_repo> gc) {
		this->_gc = gc;
	}

	int add_group() {
		return _gc->add_group();
	}
	void connect_to_group(const int group_id, const shared_ptr<session> session_ptr) override {
		this->_gc->connect_to_group(group_id, session_ptr);
	}
	 void disconnect_from_group(const int group_id, const shared_ptr<session> session_ptr) override {
		this->_gc->disconnect_from_group(group_id, session_ptr);
	}
	const unordered_set<shared_ptr<session>>& get_group_sessions(const int group_id) override {
		return this->_gc->get_group_sessions(group_id);
	}
};

