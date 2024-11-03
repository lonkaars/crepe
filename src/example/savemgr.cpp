/** \file
 * 
 * Standalone example for usage of the save manager
 */

#include <cassert>
#include <crepe/util/log.h>
#include <crepe/util/Proxy.h>
#include <crepe/api/SaveManager.h>
#include <crepe/api/Config.h>

using namespace crepe;
using namespace crepe::api;
using namespace crepe::util;

// unrelated setup code
int _ = [] () {
	// make sure all log messages get printed
	auto & cfg = Config::get_instance();
	cfg.log.level = util::LogLevel::TRACE;

	return 0; // satisfy compiler
} ();

int main() {
	const char * key = "mygame.test";

	SaveManager & mgr = SaveManager::get_instance();

	dbg_logf("has key = %s", mgr.has(key) ? "true" : "false");
	ValueBroker<int> prop = mgr.get<int>(key, 0);
	Proxy<int> val        = mgr.get<int>(key, 0);

	dbg_logf("val = %d", mgr.get<int>(key).get());
	prop.set(1);
	dbg_logf("val = %d", mgr.get<int>(key).get());
	val = 2;
	dbg_logf("val = %d", mgr.get<int>(key).get());
	mgr.set<int>(key, 3);
	dbg_logf("val = %d", mgr.get<int>(key).get());

	dbg_logf("has key = %s", mgr.has(key) ? "true" : "false");
	assert(true == mgr.has(key));

	return 0;
}

