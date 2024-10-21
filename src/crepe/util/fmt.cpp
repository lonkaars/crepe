#include <cstdarg>
#include <cstdio>
#include <string>

#include "fmt.h"

using namespace std;

string crepe::util::va_stringf(va_list args, const char * fmt) {
	va_list args_copy;
	va_copy(args_copy, args);

	size_t sz = vsnprintf(NULL, 0, fmt, args_copy) + 1;
	char * msg = (char *) malloc(sz);
	va_end(args_copy);

	vsnprintf(msg, sz, fmt, args);

	string out = msg;
	free(msg);

	va_end(args);

	return out;
}

string crepe::util::stringf(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	string out = va_stringf(args, fmt);
	va_end(args);
	return out;
}
