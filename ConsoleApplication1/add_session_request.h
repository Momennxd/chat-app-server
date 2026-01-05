#pragma once
#include "request.h"
#include "ISession_service.h"
#include "IGroup_service.h"
#include "IMessenger_service.h"
#include <utility>

class AddSessionRequest : public request {
private:
    tcp::socket _socket;
public:
    AddSessionRequest(tcp::socket&& socket) : _socket(std::move(socket)) {}

    void execute(ISession_service& ss, IGroup_service&, IMessenger_service&) override {
        ss.add_session(std::move(_socket));
    }
};

