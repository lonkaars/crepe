#pragma once

#include <soloud.h>

#include <memory>

#include "Sound.h"

namespace crepe {

class SoundSystem {
public:
	static std::unique_ptr<Sound> sound(const std::string & res);
	static std::unique_ptr<Sound> sound(std::unique_ptr<api::Resource> res);

private:
	SoundSystem();
	virtual ~SoundSystem();
	static SoundSystem instance;

private:
	SoLoud::Soloud engine;
	friend class Sound;
};

}

