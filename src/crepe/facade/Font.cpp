#include "../api/Asset.h"
#include "../api/Config.h"
#include "util/Log.h"
#include <iostream>
#include <string>

#include "Font.h"

using namespace std;
using namespace crepe;

Font::Font(const Asset & src, Mediator & mediator)
	: Resource(src, mediator) {
	dbg_trace();
	Config & config = Config::get_instance();
	const std::string FONT_PATH = src.get_path();

	this->path = FONT_PATH;

	cout << this->path << endl;
	/*
	TTF_Font * loaded_font = TTF_OpenFont(FONT_PATH.c_str(), config.font.size);
	if (loaded_font == NULL) {
		throw runtime_error(format("Font: {} (path: {})", TTF_GetError(), FONT_PATH));
	}
	this->font = {loaded_font, [](TTF_Font * font) { TTF_CloseFont(font); }};
	*/
}

TTF_Font * Font::get_font() const { return this->font.get(); }

const string & Font::get_path() const noexcept{
	return this->path;
}
