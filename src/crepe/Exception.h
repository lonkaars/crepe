#pragma once

#include <exception>
#include <string>
#include <format>

namespace crepe {

//! Exception class
class Exception : public std::exception {
public:
	//! Exception with plain message
	Exception(const std::string & msg);

	//! Exception with \c std::format message
	template<class... Args>
	Exception(std::format_string<Args...> fmt, Args&&... args);

	//! Get formatted error message
	const char * what() const noexcept;

protected:
	Exception() = default;

	//! Formatted error message
	std::string error;
};

} // namespace crepe

#include "Exception.hpp"

