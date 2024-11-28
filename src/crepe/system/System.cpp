#include "../util/Log.h"

#include "System.h"

using namespace crepe;

System::System(const Mediator & mediator) : component_manager(mediator.component_manager) { dbg_trace(); }
