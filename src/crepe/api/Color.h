#pragma once

namespace crepe {

class Color {

	// FIXME: can't these colors be defined as a `static constexpr const Color`
	// instead?

public:
	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	static const Color & get_white();
	static const Color & get_red();
	static const Color & get_green();
	static const Color & get_blue();
	static const Color & get_cyan();
	static const Color & get_magenta();
	static const Color & get_yellow();
	static const Color & get_black();

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	static Color white;
	static Color red;
	static Color green;
	static Color blue;
	static Color cyan;
	static Color magenta;
	static Color yellow;
	static Color black;

private:
	friend class crepe::SDLContext;
};

} // namespace crepe
