#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "fmt.h"
#include "log.h"
#include "../api/Config.h"

using namespace crepe::util;

static const char * const LOG_PREFIX[] = {
	[log_level::TRACE] = "[TRACE] ",
	[log_level::DEBUG] = "[DEBUG] ",
	[log_level::INFO] = "[INFO] ",
	[log_level::WARNING] = "[WARN] ",
	[log_level::ERROR] = "[ERROR] ",
};

static void log(enum log_level level, const std::string msg) {
	auto & cfg = crepe::api::Config::get_instance();
	if (level < cfg.log.level) return;

	using namespace std;
	string final = string(LOG_PREFIX[level]) + msg;
	if (!final.ends_with("\n")) final += "\n";

	// TODO: also log to file or smth
	printf("%s", final.c_str());
	fflush(stdout);
}

void crepe::util::logf(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	log(log_level::DEBUG, va_stringf(args, fmt));
	va_end(args);
}

void crepe::util::logf(log_level level, const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	log(level, va_stringf(args, fmt));
	va_end(args);
}

