#pragma once
#include <memory>
#include "IGroup_service.h"
#include "ISession_service.h"
#include "IMessenger_service.h"

class request {
public:
    virtual ~request() = default;

    virtual std::shared_ptr<response> execute(
        std::shared_ptr<ISession_service>,
        std::shared_ptr<IGroup_service>,
        std::shared_ptr<IMessenger_service>
    ) = 0;
};
