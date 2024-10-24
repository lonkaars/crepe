/** \file
 * 
 * Standalone example for usage of the logging functions
 */

#include <crepe/util/log.h>
#include <crepe/api/Config.h>

using namespace crepe;
using namespace crepe::util;

int main() {
	auto & cfg = api::Config::get_instance();
	// make sure all log messages get printed
	cfg.log.level = util::LogLevel::TRACE;

	dbg_trace();
	dbg_logf("cfg.log.color is equal to %d", cfg.log.color);
	logf(LogLevel::INFO, "info message!");
	logf(LogLevel::WARNING, "very scary warning");
	logf(LogLevel::ERROR, "fatal error!!!");

	return 0;
}

