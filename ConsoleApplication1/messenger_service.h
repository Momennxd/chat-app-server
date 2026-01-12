#pragma once
// messenger_service.cpp
#include "IMessenger_service.h"
#include "IGroup_service.h"
#include "network_layer.h"
#include "DEF_CORE.h"

#include <memory>
#include <cstdint>
#include <vector>
#include <unordered_set>

class messenger_service : public IMessenger_service {
private:
    std::shared_ptr<IGroup_service> _group_service;
public:
    messenger_service(std::shared_ptr<IGroup_service> gs) : _group_service(std::move(gs)) {}

    typed_response<uint32_t> send_message(const std::vector<uint8_t>& msg_buffer, uint32_t group_id) override {
        auto sessions_resp = _group_service->get_group_sessions(group_id);
        if (sessions_resp.status() != OK) {
            return typed_response<uint32_t>(GROUP_NOT_EXIST, 0u);
        }

        const auto& ids = sessions_resp.value();

        // Delegate actual writes to network_layer
        size_t sent_count = network_layer::write_to_sessions(ids, msg_buffer);

        return typed_response<uint32_t>(OK, static_cast<uint32_t>(sent_count));
    }
};
