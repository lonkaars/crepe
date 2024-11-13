#pragma once

#include <forward_list>

#include "System.h"

namespace crepe {

class Script;

class ScriptSystem : public System {
public:
	void update();

private:
	// TODO: to forward_list<reference_wrapper>
	std::forward_list<Script *> get_scripts() const;
};

} // namespace crepe
