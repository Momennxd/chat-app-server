#pragma once
#include "request.h"
#include "ISession_service.h"
#include "IGroup_service.h"
#include "IMessenger_service.h"
#include "DEF_CORE.h"
#include <memory>
#include <asio.hpp>
#include <stdexcept>

class connect_to_group_req : public request {
private:

    bool _executed;
    uint32_t _group_id;
	uint32_t _session_id;
public:
    explicit connect_to_group_req(uint32_t session_id, uint32_t group_id)
        : _executed(false), _group_id(group_id),
        _session_id(session_id)
    {
    }


    std::shared_ptr<response> execute(
        std::shared_ptr<ISession_service>,
        std::shared_ptr<IGroup_service> gs,
        std::shared_ptr<IMessenger_service>

    ) override
    {
        if (!gs) {
            return std::make_shared<typed_response<uint32_t>>(NOT_INIT_SERVICE, 0u);
        }

        if (_executed) {
            throw std::runtime_error("connect_to_group_req: already executed");
        }
        _executed = true;

        auto resp = gs->connect_to_group(_group_id, _session_id);
        return std::make_shared<typed_response<uint32_t>>(resp.status(), resp.value());

    }
};
