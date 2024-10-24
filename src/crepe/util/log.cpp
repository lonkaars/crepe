#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "fmt.h"
#include "log.h"
#include "../api/Config.h"

using namespace crepe::util;
using namespace std;

string log_prefix(LogLevel level) {
	switch (level) {
		case LogLevel::TRACE: return LogColor().fg_white().str("[TRACE]") + " ";
		case LogLevel::DEBUG: return LogColor().fg_magenta().str("[DEBUG]") + " ";
		case LogLevel::INFO: return LogColor().fg_blue().str("[INFO]") + " ";
		case LogLevel::WARNING: return LogColor().fg_yellow().str("[WARN]") + " ";
		case LogLevel::ERROR: return LogColor().fg_red().str("[ERROR]") + " ";
	}
	return "";
}

static void log(LogLevel level, const string msg) {
	auto & cfg = crepe::api::Config::get_instance();
	if (level < cfg.log.level) return;

	string out = log_prefix(level) + msg;
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

