#pragma once

namespace crepe::api {

class Color {

	// FIXME: can't these colors be defined as a `static constexpr const Color`
	// instead?
public:
	Color(double red, double green, double blue, double alpha);
	static const Color & get_white();
	static const Color & get_red();
	static const Color & get_green();
	static const Color & get_blue();
	static const Color & get_cyan();
	static const Color & get_magenta();
	static const Color & get_yellow();
	static const Color & get_black();

private:
	double r;
	double g;
	double b;
	double a;

	static Color white;
	static Color red;
	static Color green;
	static Color blue;
	static Color cyan;
	static Color magenta;
	static Color yellow;
	static Color black;
};

} // namespace crepe::api
