#include "session.h"
#include "group_chat.h"
#include "asio.hpp"


int session::getid()
{
	return this->m_id;
}

void session::set_id(const int id)
{
	if (id <= 0) throw runtime_error("id has to be positive");
	this->m_id = id;
}



int session::touch()
{
	this->m_last_active = std::chrono::system_clock::now();
}

int session::get_idle_time()
{
	auto now = std::chrono::system_clock::now();
	auto idle_duration = now - m_last_active; 
	return std::chrono::duration_cast<std::chrono::seconds>(idle_duration).count();
}



session::session(tcp::socket& socket, int id) : m_socket(move(socket)) {
	while (!this->m_messages.empty()) this->m_messages.pop();
	this->m_id = id;
}

void session::socket_write_async(const message& msg)
{
	if (!is_active()) return;
	this->m_messages.push(msg);
	if (this->m_messages.size() > 1) return;
	
	_do_write_async();
}

session::~session()
{
	_abort();
}


void session::close()
{
	_abort();
}

bool session::is_active()
{
	return this->m_socket.is_open();
}

void session::_do_write_async()
{
	if (this->m_messages.empty() || !this->is_active()) return;
	string& top = this->m_messages.front().msg;
	asio::async_write(this->m_socket, asio::buffer(top),
		[self = shared_from_this()](const asio::error_code& ec, size_t bytes_sent) {

			//TO DO  ==>
			//HANDLE ERROR WHEN SERVER TIRES TO TALK TO CLIENT.
			
			self->m_messages.pop();
			if (self->m_messages.size() > 0) self->_do_write_async();
		});
}

void session::_abort()
{
	error_code ec;
	if (this->is_active())
		this->m_socket.cancel(ec), m_socket.shutdown(tcp::socket::shutdown_both, ec), m_socket.close(ec);


	while (!this->m_messages.empty()) this->m_messages.pop();
}

