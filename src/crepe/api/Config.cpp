#include "Config.h"

using namespace crepe;

Config & Config::get_instance() {
	static Config instance;
	return instance;
}

