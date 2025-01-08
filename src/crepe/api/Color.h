#pragma once

#include <cstdint>

namespace crepe {

struct Color {
	uint8_t r = 0x00;
	uint8_t g = 0x00;
	uint8_t b = 0x00;
	uint8_t a = 0xff;

	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color CYAN;
	static const Color MAGENTA;
	static const Color YELLOW;
	static const Color BLACK;
	static const Color GREY;
};

} // namespace crepe
