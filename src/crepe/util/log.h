#pragma once

// allow user to disable debug macros
#ifndef CREPE_DISABLE_MACROS

#include "color.h"

// utility macros
#define _crepe_logf_here(lvl, fmt, ...) \
	crepe::util::logf(lvl, "%s%s (%s:%d)" fmt "\n", \
					  crepe::util::color::FG_WHITE, __PRETTY_FUNCTION__, \
					  __FILE_NAME__, __LINE__, crepe::util::color::RESET, \
					  __VA_ARGS__)

// very illegal global function-style macros
// NOLINTBEGIN
#define dbg_logf(fmt, ...) _crepe_logf_here(util::log_level::DEBUG, ": " fmt, __VA_ARGS__)
#define dbg_log(str) _crepe_logf_here(util::log_level::DEBUG, ": %s", str)
#define dbg_trace() _crepe_logf_here(util::log_level::TRACE, "%s", "")
// NOLINTEND

#endif

namespace crepe::util {

enum log_level {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
};

void logf(const char * fmt, ...);
void logf(enum log_level level, const char * fmt, ...);

} // namespace crepe::util
