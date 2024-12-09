#pragma once

#include <cstdint>

namespace crepe {

/**
 * struct Color - represents a color with red, green, blue and alpha values
 *
 * The `Color` struct is used to represent a color in RGBA format, where each component is an 8-bit value.
 */
struct Color {
	//! Red value (0-255)
	uint8_t r = 0x00;
	//! Green value (0-255)
	uint8_t g = 0x00;
	//! Blue value (0-255)
	uint8_t b = 0x00;
	//! Alpha value (0-255)
	uint8_t a = 0xff;

	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color CYAN;
	static const Color MAGENTA;
	static const Color YELLOW;
	static const Color BLACK;
};

} // namespace crepe
