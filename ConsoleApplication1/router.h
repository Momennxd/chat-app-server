#pragma once
#include <iostream>
#include "IGroup_service.h"
#include "ISession_service.h"
#include "IMessenger_service.h"
#include "request.h"
#include "enums.h"
#include <asio.hpp>
#include <memory>

class router
{
private:

	shared_ptr<IGroup_service> _gs;
	shared_ptr<ISession_service> _ss;
	shared_ptr<IMessenger_service> _ms;

public:

	router(shared_ptr<IGroup_service> gs, shared_ptr<ISession_service> ss, shared_ptr<IMessenger_service> ms);

	uint32_t rout(shared_ptr<request> req);

};

