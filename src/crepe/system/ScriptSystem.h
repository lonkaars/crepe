#pragma once

#include <forward_list>

#include "System.h"

namespace crepe {

class Script;

class ScriptSystem : public System {
public:
	using System::System;
	void update() override;

private:
	std::forward_list<std::reference_wrapper<Script>> get_scripts();
};

} // namespace crepe
