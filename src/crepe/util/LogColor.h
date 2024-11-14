#pragma once

#include <string>

namespace crepe {

/**
 * \brief Utility class for coloring text using ANSI escape codes
 *
 * \note Most methods in this class return a reference to \c this, which may be
 * used to chain multiple display attributes.
 */
class LogColor {
public:
	//! Get color code as stl string (or color content string)
	const std::string str(const std::string & content = "") const;

public:
	//! Reset color to default foreground and background color
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
	/**
	 * \brief Append SGR escape sequence to \c this->code
	 *
	 * \param code SGR attribute number
	 *
	 * See <https://en.wikipedia.org/wiki/ANSI_escape_code> for magic number
	 * reference.
	 */
	LogColor & add_code(unsigned int code);

private:
	//! Color escape sequence
	std::string code = "";
};

} // namespace crepe
