// network_layer.h
#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>
#include <vector>
#include <cstdint>
#include <unordered_set>

class nsession; 

class network_layer {
private:
    static std::unordered_map<uint32_t, std::shared_ptr<nsession>> _nsessions;
    static std::mutex _nsessions_mutex;

public:
    static void add_session(uint32_t id, std::shared_ptr<nsession> ses);
    static void remove_session(uint32_t id);

    static bool write_to_session(uint32_t id, const std::vector<uint8_t>& buffer);

    static size_t write_to_sessions(const std::unordered_set<uint32_t>& ids, const std::vector<uint8_t>& buffer);
};
