#include "group_chat.h"

size_t group_chat::get_sessions_count()
{
	return size_t();
}

session* group_chat::get_session(int id)
{
	if (!this->m_sessions.count(id)) throw "id does not exist";
	return this->m_sessions[id];
}

bool group_chat::add_session(session* s)
{
	if (this->m_sessions.count(s->getid())) return false;
	this->m_sessions.insert({ s->getid(), s });
}

bool group_chat::remove_session(int id)
{
	if (!this->m_sessions.count(id)) return false;
	this->m_sessions.erase(id);
	return true;
}

void group_chat::send_message_to_all_async(message& msg)
{
	for (auto it = m_sessions.begin(); it != m_sessions.end(); ++it) {
		int key = it->first;
		session* val = it->second;

		if (val != nullptr && val->is_active())
			val->socket_write_async(msg);
	}
}

