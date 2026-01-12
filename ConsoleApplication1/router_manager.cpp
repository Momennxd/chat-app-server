#include "router_manager.h"
#include "router.h"

std::shared_ptr<router> router_manager::_instance = nullptr;

void router_manager::initialize(std::shared_ptr<router> router) {
    _instance = router;
}

std::shared_ptr<router> router_manager::get_router() {
    return _instance;
}