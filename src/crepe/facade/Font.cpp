#include "../api/Config.h"
#include "util/Log.h"

#include "Font.h"

using namespace std;
using namespace crepe;

Font::Font(const Asset & src, Mediator & mediator)
	: Resource(src, mediator) {
	dbg_trace();
	Config & config = Config::get_instance();
	const std::string FONT_PATH = src.get_path();
	TTF_Font * font = TTF_OpenFont(FONT_PATH.c_str(), config.font.size);
	if (font == NULL)
		throw runtime_error(format("Font: {} (path: {})", TTF_GetError(), FONT_PATH));
	this->font = {font, [](TTF_Font * font) { TTF_CloseFont(font); }};
}

Font::~Font(){
	dbg_trace();
	this->font.reset();
}

TTF_Font * Font::get_font() const { return this->font.get(); }
