// network_layer.cpp
#include "network_layer.h"
#include "nsession.h"   
#include "services_manager.h"   
#include "ISession_service.h"   


#include <algorithm>

std::unique_ptr<asio::steady_timer> network_layer::idle_timer_;


std::unordered_map<uint32_t, std::shared_ptr<nsession>> network_layer::_nsessions;
std::mutex network_layer::_nsessions_mutex;

void network_layer::add_session(uint32_t id, std::shared_ptr<nsession> ses) {
    std::lock_guard<std::mutex> lock(_nsessions_mutex);
    _nsessions[id] = std::move(ses);
	std::cout << "Session added. Total sessions: " << _nsessions.size() << "\n";
}

void network_layer::remove_session(uint32_t id) {
    std::lock_guard<std::mutex> lock(_nsessions_mutex);
    auto s = services_manager::get_session_service();

	//remove the session from session service repository
	s->remove_session(id);

	// remove from active nsessions (session with socket)
    _nsessions.erase(id);
}


void network_layer::start_idle_monitor(asio::io_context& io,
    std::chrono::seconds check_interval,
    std::chrono::seconds idle_timeout) 
{
    std::cout << "Starting idle session monitor...\n";

    if (!idle_timer_) {
        idle_timer_ = std::make_unique<asio::steady_timer>(io);
    }

    // schedule first expiry
    idle_timer_->expires_after(check_interval);

    idle_timer_->async_wait([check_interval, idle_timeout, &io](const asio::error_code& ec) {
        if (ec && ec != asio::error::operation_aborted) {
            std::cerr << "Idle timer error: " << ec.message() << "\n";
            return;
        }
        if (!ec) {
            auto now = std::chrono::steady_clock::now();
            std::vector<uint32_t> to_remove;
            {
                std::lock_guard<std::mutex> lock(_nsessions_mutex);
                for (const auto& pair : _nsessions) {
                    auto session = pair.second;
                    if (session && session->is_active()) {
                        long long idle_seconds = session->get_idle_time();
                        if (idle_seconds > idle_timeout.count()) {
                            to_remove.push_back(pair.first);
                        }
                    }
                }
            }

            for (auto id : to_remove) {
                remove_session(id);
                std::cout << "Session " << id << " removed due to inactivity.\n";
            }

        
            if (idle_timer_) 
                idle_timer_->expires_after(check_interval);
               
			start_idle_monitor(io, check_interval, idle_timeout);
        }
        });
}


bool network_layer::write_to_session(uint32_t id, const std::vector<uint8_t>& buffer) {
    std::shared_ptr<nsession> s;
    {
        std::lock_guard<std::mutex> lock(_nsessions_mutex);
        auto it = _nsessions.find(id);
        if (it == _nsessions.end()) return false;
        s = it->second;
    }
    // call outside lock
    s->socket_write_async(buffer);
    return true;
}

size_t network_layer::write_to_sessions(const std::unordered_set<uint32_t>& ids, const std::vector<uint8_t>& buffer) {
    std::vector<std::shared_ptr<nsession>> to_write;
    {
        std::lock_guard<std::mutex> lock(_nsessions_mutex);
        to_write.reserve(ids.size());
        for (auto id : ids) {
            auto it = _nsessions.find(id);
            if (it != _nsessions.end()) to_write.push_back(it->second);
        }
    }
    for (auto& s : to_write) s->socket_write_async(buffer); // outside lock
    return to_write.size();
}
