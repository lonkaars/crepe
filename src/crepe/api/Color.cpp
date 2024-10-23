#include "Color.h"

using namespace crepe::api;

Color Color::white = Color(255, 255, 255, 0);
Color Color::red = Color(255, 0, 0, 0);
Color Color::green = Color(0, 255, 0, 0);
Color Color::blue = Color(0, 0, 255, 0);
Color Color::black = Color(0, 0, 0, 0);
Color Color::cyan = Color(0, 255, 255, 0);
Color Color::yellow = Color(255, 255, 0, 0);
Color Color::magenta = Color(255, 0, 255, 0);

Color::Color(double red, double green, double blue, double alpha) {
	this->a = alpha;
	this->r = red;
	this->g = green;
	this->b = blue;
};

const Color & Color::get_white() { return Color::white; };

const Color & Color::get_red() { return Color::red; };
const Color & Color::get_green() { return Color::green; };
const Color & Color::get_blue() { return Color::blue; };

const Color & Color::get_black() { return Color::black; };

const Color & Color::get_cyan() { return Color::cyan; };

const Color & Color::get_yellow() { return Color::yellow; };

const Color & Color::get_magenta() { return Color::magenta; };
