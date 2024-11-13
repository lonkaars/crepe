#pragma once

#include "Log.h"

namespace crepe {

template<class... Args>
void Log::logf(std::format_string<Args...> fmt, Args&&... args) {
	Log::logf(Level::INFO, fmt, std::forward<Args>(args)...);
}

template<class... Args>
void Log::logf(const Level & level, std::format_string<Args...> fmt, Args&&... args) {
	Log::log(level, std::format(fmt, std::forward<Args>(args)...));
}

}

