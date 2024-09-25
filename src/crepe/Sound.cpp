#include "Sound.h"

using namespace crepe;

Sound::Sound(std::unique_ptr<api::Resource> res) {
	_res = std::move(res);
}


