#pragma once

#include "System.h"

namespace crepe {

class ScriptSystem : public System {
public:
	static ScriptSystem & get_instance();
	virtual void update();

private:
	ScriptSystem();
	~ScriptSystem();
};

}

