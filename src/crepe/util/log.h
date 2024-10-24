#pragma once

// allow user to disable debug macros
#ifndef CREPE_DISABLE_MACROS

#include "color.h"

// utility macros
#define _crepe_logf_here(level, format, ...) \
	crepe::util::logf( \
		level, "%s" format, \
		crepe::util::LogColor().fg_white(false).fmt( \
			"%s (%s:%d)", __PRETTY_FUNCTION__, __FILE_NAME__, __LINE__), \
		__VA_ARGS__)

// very illegal global function-style macros
// NOLINTBEGIN
#define dbg_logf(fmt, ...) \
	_crepe_logf_here(crepe::util::LogLevel::DEBUG, ": " fmt, __VA_ARGS__)
#define dbg_log(str) \
	_crepe_logf_here(crepe::util::LogLevel::DEBUG, "%s: " str, "")
#define dbg_trace() _crepe_logf_here(crepe::util::LogLevel::TRACE, "%s", "")
// NOLINTEND

#endif

namespace crepe::util {

enum LogLevel {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
};

void logf(const char * fmt, ...);
void logf(enum LogLevel level, const char * fmt, ...);

} // namespace crepe::util
