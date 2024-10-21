#pragma once

#include <string>

namespace crepe::util {

std::string va_stringf(va_list args, const char * fmt);
std::string stringf(const char * fmt, ...);

} // namespace crepe::util
