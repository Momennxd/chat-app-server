// group_repo.h
#pragma once
#include "IGroup_repo.h"
#include "response.h"
#include "DEF_CORE.h"
#include <unordered_map>
#include <unordered_set>
#include <mutex>

class group_repo : public IGroup_repo {
private:
    std::unordered_map<uint32_t, std::unordered_set<uint32_t>> _group_chats;
    uint32_t groups_count = 0;
    std::mutex _gLock;
public:
    typed_response<uint32_t> add_group() override {
        std::lock_guard<std::mutex> lock(_gLock);
        ++groups_count;
        _group_chats.emplace(groups_count, std::unordered_set<uint32_t>{});
        return typed_response<uint32_t>(OK, groups_count);
    }

    typed_response<uint32_t> connect_to_group(uint32_t group_id, uint32_t session_id) override {
        std::lock_guard<std::mutex> lock(_gLock);
        auto it = _group_chats.find(group_id);
        if (it == _group_chats.end()) return typed_response<uint32_t>(GROUP_NOT_EXIST, 0);
        it->second.insert(session_id);
		cout << "Session " << session_id << " connected to group " << group_id << endl;
		cout << "group " << group_id << " now has " << it->second.size() << " sessions." << endl;
        return typed_response<uint32_t>(OK, 0);
    }

    typed_response<uint32_t> disconnect_from_group(uint32_t group_id, uint32_t session_id) override {
        std::lock_guard<std::mutex> lock(_gLock);
        auto it = _group_chats.find(group_id);
        if (it == _group_chats.end()) return typed_response<uint32_t>(GROUP_NOT_EXIST, 0);
        it->second.erase(session_id);
        return typed_response<uint32_t>(OK, 0);
    }

    typed_response<std::unordered_set<uint32_t>> get_group_sessions(uint32_t group_id) override {
        std::lock_guard<std::mutex> lock(_gLock);
        auto it = _group_chats.find(group_id);
        if (it == _group_chats.end()) return typed_response<std::unordered_set<uint32_t>>(GROUP_NOT_EXIST, {});
        return typed_response<std::unordered_set<uint32_t>>(OK, it->second);
    }
};
