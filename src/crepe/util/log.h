#pragma once

// allow user to disable debug macros
#ifndef CREPE_DISABLE_MACROS

#include "color.h"

// utility macros
#define _crepe_logf_here(fmt, ...) \
	crepe::util::logf(util::log_level::debug, "%s%s (%s:%d)" fmt "\n", \
					  crepe::util::color::FG_WHITE, __PRETTY_FUNCTION__, \
					  __FILE_NAME__, __LINE__, crepe::util::color::RESET, \
					  __VA_ARGS__)

// very illegal global function-style macros
// NOLINTBEGIN
#define dbg_logf(fmt, ...) _crepe_logf_here(": " fmt, __VA_ARGS__)
#define dbg_log(str) _crepe_logf_here(": %s", str)
#define dbg_trace() _crepe_logf_here("%s", "")
// NOLINTEND

#endif

namespace crepe::util {

enum log_level {
	debug,
	info,
	warning,
	error,
};

void logf(const char * fmt, ...);
void logf(enum log_level level, const char * fmt, ...);

} // namespace crepe::util
