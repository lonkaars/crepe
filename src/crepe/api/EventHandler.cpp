#include "EventHandler.h"

using namespace crepe;

bool IEventHandlerWrapper::exec(const Event & e) { return this->call(e); }
