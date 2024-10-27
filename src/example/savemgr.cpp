/** \file
 * 
 * Standalone example for usage of the save manager
 */

#include <cassert>
#include <crepe/util/log.h>
#include <crepe/util/Proxy.h>
#include <crepe/api/SaveManager.h>

using namespace crepe;
using namespace crepe::api;
using namespace crepe::util;

int main() {
	const char * key = "mygame.test";
	SaveManager & mgr = SaveManager::get_instance();

	ValueBroker<unsigned int> & prop = mgr.get<unsigned int>(key, 0);
	Proxy<unsigned int> val          = mgr.get<unsigned int>(key, 0);

	prop.set(1);
	val = 2;
	mgr.set<unsigned int>(key, 3);

	assert(true == mgr.has(key));

	return 0;
}

