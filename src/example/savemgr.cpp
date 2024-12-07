/** \file
 * 
 * Standalone example for usage of the save manager
 */

#include <cassert>
#include <crepe/api/Config.h>
#include <crepe/api/SaveManager.h>
#include <crepe/util/Log.h>
#include <crepe/util/Proxy.h>

using namespace crepe;

// unrelated setup code
int _ = []() {
	// make sure all log messages get printed
	auto & cfg = Config::get_instance();
	cfg.log.level = Log::Level::TRACE;

	return 0; // satisfy compiler
}();

int main() {
	const char * key = "mygame.test";

	SaveManager & mgr = SaveManager::get_instance();

	dbg_logf("has key = {}", mgr.has(key));
	ValueBroker<int> prop = mgr.get<int>(key, 0);
	Proxy<int> val = mgr.get<int>(key, 0);

	dbg_logf("val = {}", mgr.get<int>(key).get());
	prop.set(1);
	dbg_logf("val = {}", mgr.get<int>(key).get());
	val = 2;
	dbg_logf("val = {}", mgr.get<int>(key).get());
	mgr.set<int>(key, 3);
	dbg_logf("val = {}", mgr.get<int>(key).get());

	dbg_logf("has key = {}", mgr.has(key));
	assert(true == mgr.has(key));

	return 0;
}
