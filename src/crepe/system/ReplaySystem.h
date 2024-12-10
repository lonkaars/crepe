#pragma once

#include "System.h"

namespace crepe {

class ReplaySystem : public System {
public:
	using System::System;

	void fixed_update() override;
};

}

