#include "eventHandler.h"

using namespace crepe::api;
void IEventHandlerWrapper::exec(const Event & e) { call(e); }
