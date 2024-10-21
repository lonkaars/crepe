#pragma once

#include <string>

namespace crepe::util {

class LogColor {
public:
	LogColor() = default;

public:
	const char * c_str(const char * content = NULL);
	const std::string str(const std::string & content = "");

public:
	LogColor & reset();

public:
	LogColor & fg_black(bool bright = false);
	LogColor & fg_red(bool bright = false);
	LogColor & fg_green(bool bright = false);
	LogColor & fg_yellow(bool bright = false);
	LogColor & fg_blue(bool bright = false);
	LogColor & fg_magenta(bool bright = false);
	LogColor & fg_cyan(bool bright = false);
	LogColor & fg_white(bool bright = false);

public:
	LogColor & bg_black(bool bright = false);
	LogColor & bg_red(bool bright = false);
	LogColor & bg_green(bool bright = false);
	LogColor & bg_yellow(bool bright = false);
	LogColor & bg_blue(bool bright = false);
	LogColor & bg_magenta(bool bright = false);
	LogColor & bg_cyan(bool bright = false);
	LogColor & bg_white(bool bright = false);

private:
	LogColor & add_code(unsigned int code);

private:
	std::string code = "";
	std::string final = "";
};

} // namespace crepe::util::color
