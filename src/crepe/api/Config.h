#pragma once

#include <string>

#include "../util/Log.h"
#include "../types.h"

namespace crepe {

/**
 * \brief Global configuration interface
 *
 * This struct stores both engine default settings and global configuration parameters.
 */
struct Config final {
	//! Retrieve handle to global Config instance
	static Config & get_instance();

	//! Logging-related settings
	struct log { // NOLINT
		/**
		 * \brief Log level
		 *
		 * Only messages with equal or higher priority than this value will be logged.
		 */
		Log::Level level = Log::Level::INFO;
		/**
		 * \brief Enable colored log output
		 *
		 * Enables log coloring using ANSI escape codes.
		 */
		bool color = true;
	} log;

	//! Save manager
	struct savemgr { // NOLINT
		/**
		 * \brief Save file location
		 *
		 * This location is used by the constructor of SaveManager, and should be set before save
		 * manager functionality is attempted to be used.
		 */
		std::string location = "save.crepe.db";
	} savemgr;

	//! Physics-related settings
	struct physics { // NOLINT
		/**
		 * \brief gravity value of physics system
		 *
		 * Gravity value of game.
		 */
		float gravity = 10;
	} physics;

	//! Default window settings
	struct window { // NOLINT
		//! Default window size (in pixels)
		ivec2 size = {1280, 720};
		//! Default window title
		std::string title = "Jetpack joyride clone";
	} window;

	//! Asset loading options
	struct asset { // NOLINT
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

	//! Audio system settings
	struct {
		//! Max amount of simultanious voices
		unsigned int voices = 32;
	} audio;
};

} // namespace crepe
