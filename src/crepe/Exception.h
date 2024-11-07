#pragma once

#include <exception>
#include <string>

namespace crepe {

//! Exception class with printf-style constructor
class Exception : public std::exception {
public:
	//! printf
	Exception(const char * fmt, ...);
	//! Get formatted error message
	const char * what();

protected:
	Exception() = default;
	//! Formatted error message
	std::string error;

};

}
