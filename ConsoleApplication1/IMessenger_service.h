#pragma once
#include "DEF_CORE.h"
#include "message.h"
#include "session.h"
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "IGroup_service.h"
#include "ISession_service.h"

class IMessenger_service
{
public:

	virtual void send_message(int group_id, const message& msg) = 0;

};

