#pragma once

#include "../util/log.h"

namespace crepe::api {

class Config {
private:
	Config() = default;
public:
	~Config() = default;

public:
	static Config & get_instance() {
		static Config instance;
		return instance;
	}

public:
	struct {
		util::log_level level = util::log_level::INFO;
		bool color = true;
	} log;
};

}

