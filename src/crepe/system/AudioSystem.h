#pragma once

#include "../facade/SoundContext.h"

#include "System.h"

namespace crepe {

class AudioSystem : public System {
public:
	AudioSystem(SoundContext & ctx);

public:
	void update();

private:
	SoundContext & ctx;
};

} // namespace crepe

