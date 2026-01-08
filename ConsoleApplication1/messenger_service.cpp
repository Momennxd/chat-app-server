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

	typed_response<uint32_t> send_message(const vector<uint8_t>& msg_buffer, uint32_t group_id) override
	{
		auto session_set = _gr->get_group_sessions(group_id);
		if (session_set.status() == GROUP_NOT_EXIST) return typed_response<uint32_t>(GROUP_NOT_EXIST, 0);
		for (auto& s : session_set.value()) {
			if (s) {
				s->socket_write_async(msg_buffer);
			}
		}
		return typed_response<uint32_t>(OK, 0);
	}

};