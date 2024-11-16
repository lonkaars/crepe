#include "EventHandler.h"

using namespace crepe;

// Implementation of IEventHandlerWrapper::exec
bool IEventHandlerWrapper::exec(const Event & e) {
    return call(e);
}
