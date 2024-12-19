#pragma once

#include <format>

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
		TRACE, //!< Include (internal) function calls
		DEBUG, //!< Include dbg_logf output
		INFO, //!< General-purpose messages
		WARNING, //!< Non-fatal errors
		ERROR, //!< Fatal errors
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
	template <class... Args>
	static void logf(const Level & level, std::format_string<Args...> fmt, Args &&... args);

	/**
	 * \brief Format a message and log it (with default severity \c INFO)
	 *
	 * \param fmt Message format
	 * \param args Format arguments
	 */
	template <class... Args>
	static void logf(std::format_string<Args...> fmt, Args &&... args);

private:
	/**
	 * \brief Output a message prefix depending on the log level
	 *
	 * \param level Message severity
	 *
	 * \return Colored message severity prefix string
	 */
	static std::string prefix(const Level & level);
};

} // namespace crepe

#include "Log.hpp"
