#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "fmt.h"
#include "log.h"
#include "../api/Config.h"

using namespace crepe::util;
using namespace std;

string log_prefix(log_level level) {
	switch (level) {
		case log_level::TRACE: return LogColor().fg_white().str("[TRACE]") + " ";
		case log_level::DEBUG: return LogColor().fg_magenta().str("[DEBUG]") + " ";
		case log_level::INFO: return LogColor().fg_blue().str("[INFO]") + " ";
		case log_level::WARNING: return LogColor().fg_yellow().str("[WARN]") + " ";
		case log_level::ERROR: return LogColor().fg_red().str("[ERROR]") + " ";
	}
	return "";
}

static void log(enum log_level level, const string msg) {
	auto & cfg = crepe::api::Config::get_instance();
	if (level < cfg.log.level) return;

	string final = log_prefix(level) + msg;
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

