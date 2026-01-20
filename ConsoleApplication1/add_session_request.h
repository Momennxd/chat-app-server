#pragma once
#include "request.h"
#include "ISession_service.h"
#include "IGroup_service.h"
#include "IMessenger_service.h"
#include "DEF_CORE.h"
#include <memory>
#include <asio.hpp>
#include <stdexcept>

class add_session_req : public request {
private:
    asio::ip::tcp::socket _socket;
    bool _executed = false;

public:
    explicit add_session_req(asio::ip::tcp::socket&& socket)
        : _socket(std::move(socket)), _executed(false) {
    }

    std::shared_ptr<response> execute(
        std::shared_ptr<ISession_service> ss,
        std::shared_ptr<IGroup_service>,
        std::shared_ptr<IMessenger_service>

    ) override
    {
        if (!ss) {
            return std::make_shared<typed_response<uint32_t>>(NOT_INIT_SERVICE, 0u);
        }

        if (_executed) {
            throw std::runtime_error("add_session_req: already executed");
        }
        _executed = true;

        auto svc_resp = ss->add_session();

        return std::make_shared<typed_response<uint32_t>>(svc_resp.status(), svc_resp.value());
    }
};
