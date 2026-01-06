#pragma once
#include <iostream>
#include <memory>
#include "IGroup_repo.h"
#include "ISession_repo.h"

class IMessenger_service
{
public:

	virtual ~IMessenger_service() = default;
	virtual typed_response<uint32_t> send_message(uint32_t group_id, const message& msg) = 0;

};
