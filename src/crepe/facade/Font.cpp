#include "../api/Config.h"

#include "Font.h"

using namespace std;
using namespace crepe;

Font::Font(const Asset & src, Mediator & mediator)
	: Resource(src, mediator),
	  font(nullptr, TTF_CloseFont) {
	// Get the font file path from the Asset
	const std::string font_path = src.get_path();

	// Attempt to load the font
	this->font.reset(TTF_OpenFont(font_path.c_str(), Config::get_instance().font.size));

	// Check if font loading failed
	if (!this->font) {
		throw runtime_error(format("Failed to load font from path: {}. SDL_ttf error: {}",
								   font_path, TTF_GetError()));
	}
}

TTF_Font * Font::get_font() const { return this->font.get(); }
