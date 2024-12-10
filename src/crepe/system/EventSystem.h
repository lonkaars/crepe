#pragma once

#include "System.h"

namespace crepe {

class EventSystem : public System {
public:
	using System::System;

	void fixed_update() override;
};

}

