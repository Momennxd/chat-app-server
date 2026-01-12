#include "router.h"

router::router(std::shared_ptr<IGroup_service> gs,
    std::shared_ptr<ISession_service> ss,
    std::shared_ptr<IMessenger_service> ms)
    : _gs(std::move(gs)),
    _ss(std::move(ss)),
    _ms(std::move(ms))
{
}



std::shared_ptr<response> router::rout(std::shared_ptr<request> req)
{
    if (!req) throw std::runtime_error("undefined req");

    return req->execute(_ss, _gs, _ms);
}
