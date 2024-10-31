#pragma once

#include "../util/log.h"

namespace crepe::api {

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
		util::LogLevel level = util::LogLevel::INFO;
		/**
		 * \brief Colored log output
		 *
		 * Enables log coloring using ANSI escape codes.
		 */
		bool color = true;
	} log;
};

} // namespace crepe::api
