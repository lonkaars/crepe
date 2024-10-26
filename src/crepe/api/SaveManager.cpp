#include "SaveManager.h"

using namespace crepe::api;

SaveManager & SaveManager::get_instance() {
	static SaveManager instance;
	return instance;
}

