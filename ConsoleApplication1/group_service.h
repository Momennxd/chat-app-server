#pragma once
#include "IGroup_service.h"
#include "IGroup_repo.h"
#include <memory>

class group_service : public IGroup_service {
private:
    std::shared_ptr<IGroup_repo> _repo;
public:
    group_service(std::shared_ptr<IGroup_repo> repo) : _repo(std::move(repo)) {}

    typed_response<uint32_t> add_group() override { return _repo->add_group(); }
    typed_response<uint32_t> connect_to_group(uint32_t group_id, uint32_t session_id) override { return _repo->connect_to_group(group_id, session_id); }
    typed_response<uint32_t> disconnect_from_group(uint32_t group_id, uint32_t session_id) override { return _repo->disconnect_from_group(group_id, session_id); }
    typed_response<std::unordered_set<uint32_t>> get_group_sessions(uint32_t group_id) override { return _repo->get_group_sessions(group_id); }
};
