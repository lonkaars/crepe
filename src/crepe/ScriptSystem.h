#pragma once

#include <forward_list>

#include "System.h"

namespace crepe::api {
class Script;
}

namespace crepe {

class ScriptSystem : public System {
public:
	static ScriptSystem & get_instance();
	void update();

private:
	ScriptSystem();
	~ScriptSystem();

private:
	std::forward_list<api::Script *> get_scripts();
};

} // namespace crepe
