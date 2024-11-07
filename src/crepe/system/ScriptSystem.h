#pragma once

#include <forward_list>

#include "System.h"

namespace crepe {

class Script;

class ScriptSystem : public System {
public:
	static ScriptSystem & get_instance();
	void update();

private:
	ScriptSystem();
	~ScriptSystem();

private:
	// TODO: to forward_list<reference_wrapper>
	std::forward_list<Script *> get_scripts();
};

} // namespace crepe
