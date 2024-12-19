#pragma once

#include "Log.h"
#include "LogColor.h"

// utility macros
#define _crepe_logf_here(level, fmt, ...) \
	crepe::Log::logf(level, "{}" fmt, \
					 crepe::LogColor().fg_white(false).str(std::format( \
						 "{} ({}:{})", __PRETTY_FUNCTION__, __FILE_NAME__, __LINE__)), \
					 __VA_ARGS__)

// very illegal global function-style macros
// NOLINTBEGIN
#define dbg_logf(fmt, ...) _crepe_logf_here(crepe::Log::Level::DEBUG, ": " fmt, __VA_ARGS__)
#define dbg_log(str) _crepe_logf_here(crepe::Log::Level::DEBUG, ": {}", str)
#define dbg_trace() _crepe_logf_here(crepe::Log::Level::TRACE, "", "")
// NOLINTEND
