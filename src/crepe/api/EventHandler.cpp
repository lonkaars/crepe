#include "EventHandler.h"
bool IEventHandlerWrapper::exec(const Event & e) { return call(e); }
