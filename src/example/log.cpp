/** \file
 * 
 * Standalone example for usage of the logging functions
 */

#include <crepe/api/Config.h>
#include <crepe/util/Log.h>

using namespace crepe;

// unrelated setup code
int _ = []() {
	// make sure all log messages get printed
	auto & cfg = Config::get_instance();
	cfg.log.level = Log::Level::TRACE;

	return 0; // satisfy compiler
}();

int main() {
	dbg_trace();
	dbg_log("debug message");
	Log::logf("info message with variable: {}", 3);
	Log::logf(Log::Level::WARNING, "warning");
	Log::logf(Log::Level::ERROR, "error");
	

	return 0;
}
