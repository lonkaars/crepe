#include "../util/Log.h"

#include "System.h"

using namespace crepe;

System::System(ComponentManager & mgr) : component_manager(mgr) { dbg_trace(); }
