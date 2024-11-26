#pragma once

#include "../facade/SoundContext.h"
#include "../ResourceManager.h"

#include "System.h"

namespace crepe {

class AudioSystem : public System {
public:
	using System::System;
	void update() override;

private:
	SoundContext context {};
	ResourceManager resource_manager {};
};

} // namespace crepe

