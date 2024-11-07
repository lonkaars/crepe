#include <cstdarg>

#include "../api/Config.h"
#include "LogColor.h"

#include "fmt.h"

using namespace crepe;
using namespace std;

static constexpr const char * RESET_CODE = "\e[0m";

const string LogColor::str(const string & content) {
	auto & cfg = Config::get_instance();
	string out = content;
	if (cfg.log.color) out = this->code + out;
	if (content.size() == 0) return out;
	if (cfg.log.color) out = out + RESET_CODE;
	return out;
}

const char * LogColor::c_str(const char * content) {
	this->final = this->str(content == NULL ? "" : content);
	return this->final.c_str();
}

const char * LogColor::fmt(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	string content = va_stringf(args, fmt);
	va_end(args);
	return this->c_str(content.c_str());
}

LogColor & LogColor::add_code(unsigned int code) {
	this->code += stringf("\e[%dm", code);
	return *this;
}

LogColor & LogColor::reset() {
	this->code = RESET_CODE;
	return *this;
}

LogColor & LogColor::fg_black(bool bright) {
	return this->add_code(bright ? 90 : 30);
}
LogColor & LogColor::fg_red(bool bright) {
	return this->add_code(bright ? 91 : 31);
}
LogColor & LogColor::fg_green(bool bright) {
	return this->add_code(bright ? 92 : 32);
}
LogColor & LogColor::fg_yellow(bool bright) {
	return this->add_code(bright ? 93 : 33);
}
LogColor & LogColor::fg_blue(bool bright) {
	return this->add_code(bright ? 94 : 34);
}
LogColor & LogColor::fg_magenta(bool bright) {
	return this->add_code(bright ? 95 : 35);
}
LogColor & LogColor::fg_cyan(bool bright) {
	return this->add_code(bright ? 96 : 36);
}
LogColor & LogColor::fg_white(bool bright) {
	return this->add_code(bright ? 97 : 37);
}
LogColor & LogColor::bg_black(bool bright) {
	return this->add_code(bright ? 100 : 40);
}
LogColor & LogColor::bg_red(bool bright) {
	return this->add_code(bright ? 101 : 41);
}
LogColor & LogColor::bg_green(bool bright) {
	return this->add_code(bright ? 102 : 42);
}
LogColor & LogColor::bg_yellow(bool bright) {
	return this->add_code(bright ? 103 : 43);
}
LogColor & LogColor::bg_blue(bool bright) {
	return this->add_code(bright ? 104 : 44);
}
LogColor & LogColor::bg_magenta(bool bright) {
	return this->add_code(bright ? 105 : 45);
}
LogColor & LogColor::bg_cyan(bool bright) {
	return this->add_code(bright ? 106 : 46);
}
LogColor & LogColor::bg_white(bool bright) {
	return this->add_code(bright ? 107 : 47);
}
