#include <cstdarg>
#include <cstdio>
#include <string>

#include "fmt.h"

using namespace std;

string crepe::va_stringf(va_list args, const char * fmt) {
	string out;

	va_list args_copy;
	va_copy(args_copy, args);
	size_t length = vsnprintf(NULL, 0, fmt, args_copy);
	// resize to include terminating null byte
	out.resize(length + 1);
	va_end(args_copy);

	// vsnprintf adds terminating null byte
	vsnprintf(out.data(), out.size(), fmt, args);
	// resize to actual length
	out.resize(length);

	va_end(args);

	return out;
}

string crepe::stringf(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	string out = va_stringf(args, fmt);
	va_end(args);
	return out;
}
