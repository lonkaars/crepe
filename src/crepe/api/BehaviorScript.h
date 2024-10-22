#pragma once

#include "../Component.h"
#include "../Script.h"

namespace crepe::api {

class BehaviorScript : public Script, public Component {
	// only allow ComponentManager to instantiate scripts
	friend class ComponentManager;

protected:
	BehaviorScript();
};

} // namespace crepe::api
