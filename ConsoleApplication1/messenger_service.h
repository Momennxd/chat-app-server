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
#include "BIT.h"

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
        if (msg_buffer.size() < 12) {
            return typed_response<uint32_t>(UNDEFINED_REQUEST, 0u);
		}
        auto ids = sessions_resp.value();
		int current_session_id = BIT::bytes_to_uint32(msg_buffer.data() + 4);
		ids.erase(current_session_id); // do not send the message back to the sender
		cout << "Sending message to group " << group_id << " to " << ids.size() << " sessions." << endl;
        cout << endl;

		vector<uint8_t> new_buffer(msg_buffer.size() + 8);
		auto size_bytes = BIT::uint32_to_bytes_buffer(static_cast<uint32_t>(msg_buffer.size() + 4));
		auto req_type_bytes = BIT::uint32_to_bytes_buffer(static_cast<uint32_t>(request_type::SEND_MESSAGE));

		// copy size bytes
		std::copy(size_bytes.begin(), size_bytes.end(), new_buffer.begin());

		// copy req type bytes
		std::copy(req_type_bytes.begin(), req_type_bytes.end(), new_buffer.begin() + 4);


		//copy rest of the message
        std::copy(msg_buffer.begin(), msg_buffer.end(), new_buffer.begin() + 8);


        // Delegate actual writes to network_layer
        size_t sent_count = network_layer::write_to_sessions(ids, new_buffer);

        return typed_response<uint32_t>(OK, static_cast<uint32_t>(sent_count));
    }
};
