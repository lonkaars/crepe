#include "System.h"

using namespace crepe;

// TODO: ComponentManager shouldn't be a singleton
System::System() : compmgr(ComponentManager::get_instance()) {}

