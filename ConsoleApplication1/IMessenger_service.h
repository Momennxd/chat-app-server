#pragma once
#include <iostream>
#include <memory>
#include "IGroup_repo.h"
#include "ISession_repo.h"

class IMessenger_service
{
public:

	virtual ~IMessenger_service() = default;
	virtual void send_message(int group_id, const message& msg) = 0;

};
