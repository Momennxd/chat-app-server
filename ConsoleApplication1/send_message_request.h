#pragma once
#include "request.h"
#include "ISession_service.h"
#include "IGroup_service.h"
#include "IMessenger_service.h"
#include "DEF_CORE.h"
#include <memory>
#include <asio.hpp>
#include <stdexcept>

class send_message_req : public request {
private:

    bool _executed;
    uint32_t _group_id;
    vector<uint8_t> _msg_buffer;
public:
    explicit send_message_req(std::vector<uint8_t> msg_buffer, uint32_t group_id)
        : _executed(false), _group_id(group_id),
        _msg_buffer(std::move(msg_buffer))
    {
    }


    std::shared_ptr<response> execute(
        std::shared_ptr<ISession_service>,
        std::shared_ptr<IGroup_service>,
        std::shared_ptr<IMessenger_service> ms

    ) override
    {
        if (!ms) {
            return std::make_shared<typed_response<uint32_t>>(NOT_INIT_SERVICE, 0u);
        }

        if (_executed) {
            throw std::runtime_error("send_message_req: already executed");
        }
        _executed = true;

        auto resp = ms->send_message(_msg_buffer, _group_id);
        return std::make_shared<typed_response<uint32_t>>(resp.status(), resp.value());

    }
};
