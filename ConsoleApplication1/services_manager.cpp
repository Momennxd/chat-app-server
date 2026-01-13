#include "services_manager.h"
#include "IGroup_service.h"
#include "ISession_service.h"
#include "IMessenger_service.h"


std::shared_ptr<IGroup_service> services_manager::group_service_ = nullptr;
std::shared_ptr<ISession_service> services_manager::session_service_ = nullptr;
std::shared_ptr<IMessenger_service> services_manager::messenger_service_ = nullptr;


std::shared_ptr<IGroup_service> services_manager::get_group_service()
{
	return services_manager::group_service_;
}

std::shared_ptr<ISession_service> services_manager::get_session_service()
{
	return services_manager::session_service_;
}

std::shared_ptr<IMessenger_service> services_manager::get_messenger_service()
{
	return services_manager::messenger_service_;
}

void services_manager::initialize(std::shared_ptr<IGroup_service> gs, std::shared_ptr<ISession_service> ss, std::shared_ptr<IMessenger_service> ms)
{
	services_manager::group_service_ = gs;
	services_manager::session_service_ = ss;
	services_manager::messenger_service_ = ms;
}
