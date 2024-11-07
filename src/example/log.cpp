/** \file
 * 
 * Standalone example for usage of the logging functions
 */

#include <crepe/api/Config.h>
#include <crepe/util/log.h>

using namespace crepe;

// unrelated setup code
int _ = []() {
	// make sure all log messages get printed
	auto & cfg = Config::get_instance();
	cfg.log.level = LogLevel::TRACE;

	return 0; // satisfy compiler
}();

int main() {
	dbg_trace();
	dbg_logf("test printf parameters: %d", 3);
	logf(LogLevel::INFO, "info message");
	logf(LogLevel::WARNING, "warning");
	logf(LogLevel::ERROR, "error");

	return 0;
}
