#include "router.h"

router::router(shared_ptr<IGroup_service> gs, shared_ptr<ISession_service> ss, shared_ptr<IMessenger_service> ms)
{
	this->_gs = gs;
	this->_ss = ss;
	this->_ms = ms;
}

uint32_t router::rout(shared_ptr<request> req)
{
	if (req == nullptr) return 0;
	req->execute(*_ss, *_gs, *_ms);
	return 1;
}
