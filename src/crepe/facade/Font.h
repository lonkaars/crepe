#pragma once

#include <memory>
#include <SDL2/SDL_ttf.h>

#include "../api/Asset.h"
#include "../api/Config.h"

namespace crepe {

/**
 * \brief Font resource facade
 *
 * This class is a wrapper around an SDL_ttf font instance, encapsulating font loading and usage.
 */
class Font : public Resource{
public:
    /**.
	 * \param src Asset with texture data to load.
	 * \param mediator use the SDLContext reference to load the image
	 */
    Font(const Asset & src, Mediator & mediator);


    ~Font() = default
	const TTF_Font& get_font() const;
private:
	//! The SDL_ttf font object with custom deleter.
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;
	int default_font_size = Config::get_instance().font.font_size;
};

} // namespace crepe
