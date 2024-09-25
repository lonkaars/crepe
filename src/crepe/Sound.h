#pragma once

#include <soloud.h>

#include <memory>

#include "api/Resource.h"

namespace crepe {

class Sound {
public:
	Sound(std::unique_ptr<api::Resource> res);
	virtual ~Sound() = default;

public:
	void pause();
	void play();
	void rewind();
	void set_volume(float volume);
	void set_looping(bool looping);

private:
	std::unique_ptr<api::Resource> _res;
	SoLoud::handle _handle;
	bool _paused;
};

}

