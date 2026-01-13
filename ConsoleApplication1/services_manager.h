#pragma once
#include <memory>

class IGroup_service;
class ISession_service;
class IMessenger_service;

class services_manager
{
public:
	static std::shared_ptr<IGroup_service> get_group_service();

	static std::shared_ptr<ISession_service> get_session_service();

	static std::shared_ptr<IMessenger_service> get_messenger_service();

	static void initialize(
		std::shared_ptr<IGroup_service> gs,
		std::shared_ptr<ISession_service> ss,
		std::shared_ptr<IMessenger_service> ms);
	




private:

	static std::shared_ptr<IGroup_service> group_service_;
	static std::shared_ptr<ISession_service> session_service_;
	static std::shared_ptr<IMessenger_service> messenger_service_;

};