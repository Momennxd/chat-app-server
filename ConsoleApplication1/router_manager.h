#pragma once
#include <memory>

class router;

class router_manager {
public:
    static void initialize(std::shared_ptr<router> router);
    static std::shared_ptr<router> get_router();

private:
    static std::shared_ptr<router> _instance;
};