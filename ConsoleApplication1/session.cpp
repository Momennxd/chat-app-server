#include "session.h"

int session::getid() const
{
	return this->m_id;
}

void session::set_id(const int id)
{
	if (id <= 0) throw runtime_error("id has to be positive");
	this->m_id = id;
}

string session::get_name() const
{
	return this->m_name;
}

void session::set_name(const string& name)
{
	if (name.size() == 0) return;
	this->m_name = name;
}



void session::touch()
{
	this->m_last_active = std::chrono::system_clock::now();
}

int session::get_idle_time()
{
	auto now = std::chrono::system_clock::now();
	auto idle_duration = now - m_last_active;
	return std::chrono::duration_cast<std::chrono::seconds>(idle_duration).count();
}



session::session(int id) : m_id(id) {
	this->touch();
}



session::~session()
{

}

