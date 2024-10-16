#pragma once

#include "../Script.h"
#include "../Component.h"

namespace crepe::api {

class BehaviorScript : public Script, public Component {
	// only allow ComponentManager to instantiate scripts
	friend class ComponentManager;

protected:
	BehaviorScript();
};

}

