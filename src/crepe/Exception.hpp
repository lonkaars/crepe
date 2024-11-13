#pragma once

#include "Exception.h"

namespace crepe {

template <class... Args>
Exception::Exception(std::format_string<Args...> fmt, Args &&... args) {
	this->error = std::format(fmt, std::forward<Args>(args)...);
}

} // namespace crepe
