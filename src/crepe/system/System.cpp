#include "../util/Log.h"

#include "System.h"

using namespace crepe;

System::System(const Mediator & mediator) : mediator(mediator) { dbg_trace(); }
