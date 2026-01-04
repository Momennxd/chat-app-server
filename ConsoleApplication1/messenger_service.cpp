#include "IMessenger_service.h"

class messenger_service : IMessenger_service
{
private:

	shared_ptr<IGroup_repo> _gr;
	shared_ptr<ISession_repo> _sr;

public:
	messenger_service(std::shared_ptr<IGroup_repo> gs,
		std::shared_ptr<ISession_repo> ss)
		: _gr(std::move(gs)), _sr(std::move(ss))
	{
	}

	void send_message(int group_id, const message& msg) override
	{
		auto session_set = _gr->get_group_sessions(group_id);
		for (auto& s : session_set) {
			if (s) {
				s->socket_write_async(msg);
			}
		}

	}

};