#pragma once

#include "../util/log.h"

namespace crepe {

class Config {
private:
	Config() = default;

public:
	~Config() = default;

public:
	//! Retrieve handle to global Config instance
	static Config & get_instance() {
		static Config instance;
		return instance;
	}

public:
	//! Logging-related settings
	struct {
		/**
		 * \brief Log level
		 *
		 * Only messages with equal or higher priority than this value will be
		 * logged.
		 */
		LogLevel level = LogLevel::INFO;
		/**
		 * \brief Colored log output
		 *
		 * Enables log coloring using ANSI escape codes.
		 */
		bool color = true;
	} log;

	//! Save manager
	struct {
		std::string location = "save.crepe.db";
	} savemgr;
};

} // namespace crepe
