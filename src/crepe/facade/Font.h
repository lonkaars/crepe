#pragma once

#include <memory>
#include <SDL2/SDL_ttf.h>

#include "../api/Asset.h"
#include "../api/Config.h"

namespace crepe {

/**
 * \brief Resource for managing font creation and destruction
 *
 * This class is a wrapper around an SDL_ttf font instance, encapsulating font loading and usage.
 */
class Font : public Resource{
public:
    /**
	 * \param src Asset with font data to load.
	 * \param mediator use the SDLContext reference to get_font()
	 */
    Font(const Asset & src, Mediator & mediator);

	/**
	 * \brief getter for TTF_Font
	 * 
	 * \param src Asset with font data to load.
	 * \param mediator use the SDLContext reference to get_font()
	 */
	TTF_Font* get_font() const;
private:
	//! The SDL_ttf font object with custom deleter.
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font;
};

} // namespace crepe
