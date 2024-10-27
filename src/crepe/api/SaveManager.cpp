#include "../DB.h"
#include "util/log.h"

#include "SaveManager.h"

using namespace std;
using namespace crepe;
using namespace crepe::api;

SaveManager::SaveManager() {
	dbg_trace();
	this->db = make_unique<DB>("./save.crepe.db");
}

SaveManager & SaveManager::get_instance() {
	dbg_trace();
	static SaveManager instance;
	return instance;
}

