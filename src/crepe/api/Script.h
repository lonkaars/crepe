#pragma once

namespace crepe {
class ScriptSystem;
}

namespace crepe::api {

class Script {
	friend class crepe::ScriptSystem;
protected:
	virtual void init() {}
	virtual void update() {}
	// NOTE: additional *events* (like unity's OnDisable and OnEnable) should be
	// implemented as member methods in derivative user script classes and
	// registered in init(), otherwise this class will balloon in size with each
	// added event.
};

}

