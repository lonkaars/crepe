#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "log.h"

using namespace crepe::util;

static const char * const LOG_PREFIX[] = {
	[log_level::debug] = "[DBG] ",
	[log_level::info] = "[INFO] ",
	[log_level::warning] = "[WARN] ",
	[log_level::error] = "[ERR] ",
};

static void va_logf(enum log_level level, va_list args, const std::string fmt) {
	va_list args_copy;
	va_copy(args_copy, args);

	// prepend log level and ensure newline
	std::string format_fixed = LOG_PREFIX[level] + fmt;
	if (!format_fixed.ends_with("\n")) format_fixed += "\n";

	size_t sz = vsnprintf(NULL, 0, format_fixed.c_str(), args_copy) + 1;
	char * msg = (char *) malloc(sz);
	va_end(args_copy);

	vsnprintf(msg, sz, format_fixed.c_str(), args);

	// TODO: also log to file or smth
	printf("%s", msg);
	fflush(stdout);

	free(msg);
}

void crepe::util::logf(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	va_logf(crepe::util::log_level::debug, args, fmt);
	va_end(args);
}

void crepe::util::logf(log_level level, const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	va_logf(level, args, fmt);
	va_end(args);
}

