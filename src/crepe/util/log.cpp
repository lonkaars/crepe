#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "fmt.h"
#include "log.h"

using namespace crepe::util;

static const char * const LOG_PREFIX[] = {
	[LogLevel::DEBUG] = "[DBG] ",
	[LogLevel::INFO] = "[INFO] ",
	[LogLevel::WARNING] = "[WARN] ",
	[LogLevel::ERROR] = "[ERR] ",
};

static void log(LogLevel level, const std::string & msg) {
	using namespace std;
	string out = string(LOG_PREFIX[level]) + msg;
	if (!out.ends_with("\n")) out += "\n";

	// TODO: also log to file or smth
	printf("%s", out.c_str());
	fflush(stdout);
}

void crepe::util::logf(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	log(LogLevel::DEBUG, va_stringf(args, fmt));
	va_end(args);
}

void crepe::util::logf(LogLevel level, const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	log(level, va_stringf(args, fmt));
	va_end(args);
}
