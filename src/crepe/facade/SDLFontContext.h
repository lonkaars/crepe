#pragma once

#include <SDL2/SDL_ttf.h>
#include <fontconfig/fontconfig.h>
#include <memory>

#include "../api/Asset.h"

namespace crepe {
class SDLFontContext {
public:
	SDLFontContext();
	~SDLFontContext();
	SDLFontContext(const SDLFontContext &) = delete;
	SDLFontContext(SDLFontContext &&) = delete;
	SDLFontContext & operator=(const SDLFontContext &) = delete;
	SDLFontContext & operator=(SDLFontContext &&) = delete;
	/**
		 * 
		 * \brief Facade function to convert a font_family into an asset.
		 * 
		 * This function uses the FontConfig library to convert a font family name (Arial, Inter, Helvetica) and converts it to the font source path.
		 * 
		 * \param font_family Name of the font family name.
		 */
	Asset get_font_asset(const std::string font_family);

private:
};

} // namespace crepe
