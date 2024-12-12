#include <iostream>
#include <string>

#include "../api/Config.h"

#include "Log.h"
#include "LogColor.h"

using namespace crepe;
using namespace std;

string Log::prefix(const Level & level) {
	switch (level) {
		case Level::TRACE:
			return LogColor().fg_white().str("[TRACE]") + " ";
		case Level::DEBUG:
			return LogColor().fg_magenta().str("[DEBUG]") + " ";
		case Level::INFO:
			return LogColor().fg_blue().str("[INFO]") + " ";
		case Level::WARNING:
			return LogColor().fg_yellow().str("[WARN]") + " ";
		case Level::ERROR:
			return LogColor().fg_red().str("[ERROR]") + " ";
	}
	return "";
}

void Log::log(const Level & level, const string & msg) {
	auto & cfg = Config::get_instance();
	if (level < cfg.log.level) return;

	string out = Log::prefix(level) + msg;
	if (!out.ends_with("\n")) out += "\n";

	// TODO: also log to file or smth
	cout.write(out.data(), out.size());
	cout.flush();
}
