#pragma once

#include "../facade/SoundContext.h"
#include "../api/ResourceManager.h"

#include "System.h"

namespace crepe {

class AudioSystem : public System {
public:
	using System::System;
	void update() override;

private:
	SoundContext context {};
	ResourceManager & resman = ResourceManager::get_instance();
};

} // namespace crepe

