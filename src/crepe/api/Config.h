#pragma once

#include "../util/Log.h"

namespace crepe {

/**
 * \brief Global configuration interface
 *
 * This class stores engine default settings. Properties on this class are only supposed to be
 * modified *before* execution is handed over from the game programmer to the engine (i.e. the
 * main loop is started).
 */
class Config final {
public:
	//! Retrieve handle to global Config instance
	static Config & get_instance();

private:
	Config() = default;
	~Config() = default;
	Config(const Config &) = default;
	Config(Config &&) = default;
	Config & operator=(const Config &) = default;
	Config & operator=(Config &&) = default;

public:
	//! Logging-related settings
	struct {
		/**
		 * \brief Log level
		 *
		 * Only messages with equal or higher priority than this value will be logged.
		 */
		Log::Level level = Log::Level::DEBUG;
		/**
		 * \brief Colored log output
		 *
		 * Enables log coloring using ANSI escape codes.
		 */
		bool color = true;
	} log;

	//! Save manager
	struct {
		/**
		 * \brief Save file location
		 *
		 * This location is used by the constructor of SaveManager, and should be set before save
		 * manager functionality is attempted to be used.
		 */
		std::string location = "save.crepe.db";
	} savemgr;

	//! physics-related settings
	struct {
		/**
		 * \brief gravity value of physics system
		 *
		 * Gravity value of game.
		 */
		double gravity = 1;
	} physics;

	//! Asset loading options
	struct {
		/**
		 * \brief Pattern to match for Asset base directory
		 *
		 * All non-absolute paths resolved using \c Asset will be made relative to
		 * the first parent directory relative to the calling executable where
		 * appending this pattern results in a path that exists. If this string is
		 * empty, path resolution is disabled, and Asset will return all paths
		 * as-is.
		 */
		std::string root_pattern = ".crepe-root";
	} asset;
};

} // namespace crepe
