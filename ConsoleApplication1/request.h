#pragma once
#include "enums.h";
#include "message.h";
#include "ISession_service.h";
#include "IGroup_service.h";
#include "IMessenger_service.h";

//netowrk ->(buffer) -> req parser -> (req object) -> router -> target service
class request {
public:
    virtual ~request() = default;
    virtual void execute(ISession_service&, IGroup_service&, IMessenger_service&) = 0;
};

