/** \file
 * 
 * Standalone example for usage of the save manager
 */

#include <cassert>
#include <crepe/util/log.h>
#include <crepe/api/SaveManager.h>

using namespace crepe;
using namespace crepe::api;
using namespace crepe::util;

int main() {
	const char * key = "mygame.test";
	SaveManager & mgr = SaveManager::get_instance();

	auto & prop = mgr.get<unsigned int>(key, 1);
	prop = 2;

	mgr.set<unsigned int>(key, 3);

	assert(true == mgr.has(key));

	return 0;
}

