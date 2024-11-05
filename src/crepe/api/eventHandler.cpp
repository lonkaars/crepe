#include "eventHandler.h"

using namespace crepe;
void IEventHandlerWrapper::exec(const Event & e) { call(e); }
