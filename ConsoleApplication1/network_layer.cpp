// network_layer.cpp
#include "network_layer.h"
#include "nsession.h"   
#include <algorithm>


std::unordered_map<uint32_t, std::shared_ptr<nsession>> network_layer::_nsessions;
std::mutex network_layer::_nsessions_mutex;

void network_layer::add_session(uint32_t id, std::shared_ptr<nsession> ses) {
    std::lock_guard<std::mutex> lock(_nsessions_mutex);
    _nsessions[id] = std::move(ses);
	std::cout << "Session added. Total sessions: " << _nsessions.size() << "\n";
}

void network_layer::remove_session(uint32_t id) {
    std::lock_guard<std::mutex> lock(_nsessions_mutex);
    _nsessions.erase(id);
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
