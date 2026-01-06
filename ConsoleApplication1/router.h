#pragma once
#include <memory>
#include "request.h"
#include "IGroup_service.h"
#include "ISession_service.h"
#include "IMessenger_service.h"
#include <stdexcept>

class router
{
private:
    std::shared_ptr<IGroup_service> _gs;
    std::shared_ptr<ISession_service> _ss;
    std::shared_ptr<IMessenger_service> _ms;

public:
    router(std::shared_ptr<IGroup_service> gs,
        std::shared_ptr<ISession_service> ss,
        std::shared_ptr<IMessenger_service> ms);

    std::shared_ptr<response> rout(std::shared_ptr<request> req);
};
