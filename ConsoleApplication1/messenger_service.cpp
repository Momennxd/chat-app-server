#include "IMessenger_service.h"

class messenger_service : public IMessenger_service
{
private:

	shared_ptr<IGroup_service> _gs;
	shared_ptr<ISession_service> _ss;

public:
	messenger_service(shared_ptr<IGroup_service> gs, shared_ptr<ISession_service> ss) {
		this->_gs = gs;
		this->_ss = ss;
	}

	void send_message(int group_id, const message& msg)
	{
		auto session_set = _gs->get_group_sessions(group_id);
		for (auto& s : session_set) {
			if (s) {
				s->socket_write_async(msg);
			}
		}
	
	}

};