#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "log.h"
#include "fmt.h"

using namespace crepe::util;

static const char * const LOG_PREFIX[] = {
	[log_level::DEBUG] = "[DBG] ",
	[log_level::INFO] = "[INFO] ",
	[log_level::WARNING] = "[WARN] ",
	[log_level::ERROR] = "[ERR] ",
};

static void log(enum log_level level, const std::string msg) {
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

