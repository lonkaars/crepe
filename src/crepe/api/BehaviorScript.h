#pragma once

#include "../Script.h"
#include "../Component.h"

namespace crepe::api {

class BehaviorScript : public Script, public Component {
protected:
	// only allow ComponentManager to instantiate scripts
	friend class ComponentManager;
	BehaviorScript();
public:
	// but allow uniqe_ptr to call the destructor (THIS IS VERY IMPORTANT)
	virtual ~BehaviorScript() = default;

	static BehaviorScript * component;
};

}

