#include <cstdarg>

#include "Exception.h"
#include "util/fmt.h"

using namespace std;
using namespace crepe;

const char * Exception::what() const noexcept { return error.c_str(); }

Exception::Exception(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	this->error = va_stringf(args, fmt);
	va_end(args);
}

