#include "../api/Asset.h"
#include "../util/Log.h"

#include "Sound.h"

using namespace crepe;
using namespace std;

Sound::Sound(const Asset & src) : Resource(src) {
	this->sample.load(src.get_path().c_str());
	dbg_trace();
}
Sound::~Sound() { dbg_trace(); }
