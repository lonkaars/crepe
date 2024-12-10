#pragma once

#include <memory>
#include <SDL2/SDL_ttf.h>

#include "../api/Asset.h"

namespace crepe {

/**
 * \brief Font resource facade
 *
 * This class is a wrapper around an SDL_ttf font instance, encapsulating font loading and usage.
 */
class Font : public Resource{
public:
    /**
     * \param res A unique pointer to an Asset holding the font resource.
     */
    Font(const Asset & src, Mediator & mediator);

    /**
     * \brief Destructor to clean up font resources.
     */
    ~Font() = default;
private:
	//! The SDL_ttf font object with custom deleter.
    std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)> font; 
};

} // namespace crepe
