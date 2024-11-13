#pragma once

#include <format>

// allow user to disable debug macros
#ifndef CREPE_DISABLE_MACROS

#include "LogColor.h"

// utility macros
#define _crepe_logf_here(level, fmt, ...) crepe::Log::logf(level, "{}" fmt, crepe::LogColor().fg_white(false).str(std::format("{} ({}:{})", __PRETTY_FUNCTION__, __FILE_NAME__, __LINE__)), __VA_ARGS__)

// very illegal global function-style macros
// NOLINTBEGIN
#define dbg_logf(fmt, ...) \
	_crepe_logf_here(crepe::Log::Level::DEBUG, ": " fmt, __VA_ARGS__)
#define dbg_log(str) _crepe_logf_here(crepe::Log::Level::DEBUG, ": {}", str)
#define dbg_trace() _crepe_logf_here(crepe::Log::Level::TRACE, "", "")
// NOLINTEND

#endif

namespace crepe {

/**
 * \brief Logging utility
 *
 * This class is used to output log messages to the console and/or log files.
 */
class Log {
public:
	//! Log message severity
	enum Level {
		TRACE, //< Include (internal) function calls
		DEBUG, //< Include dbg_logf output
		INFO, //< General-purpose messages
		WARNING, //< Non-fatal errors
		ERROR, //< Fatal errors
	};

	/**
	 * \brief Log a formatted message
	 *
	 * \param level Message severity
	 * \param msg Formatted message
	 */
	static void log(const Level & level, const std::string & msg);

	/**
	 * \brief Format a message and log it
	 *
	 * \param level Message severity
	 * \param fmt Message format
	 * \param args Format arguments
	 */
	template<class... Args>
	static void logf(const Level & level, std::format_string<Args...> fmt, Args&&... args);

	/**
	 * \brief Format a message and log it (with default severity \c INFO)
	 *
	 * \param fmt Message format
	 * \param args Format arguments
	 */
	template<class... Args>
	static void logf(std::format_string<Args...> fmt, Args&&... args);

private:
	/**
	 * \brief Output a message prefix depending on the log level
	 *
	 * \param level Message severity
	 */
	static std::string prefix(const Level & level);
};

} // namespace crepe

#include "Log.hpp"

