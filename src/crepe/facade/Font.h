#pragma once

#include <SDL2/SDL_ttf.h>
#include <memory>

#include "../Resource.h"
#include "../api/Config.h"

namespace crepe {

class Asset;
/**
 * \brief Resource for managing font creation and destruction
 *
 * This class is a wrapper around an SDL_ttf font instance, encapsulating font loading and usage.
 * It loads a font from an Asset and manages its lifecycle. The font is automatically unloaded
 * when this object is destroyed.
 */
class Font : public Resource {

public:
	/**
     * \param src The Asset containing the font file path and metadata to load the font.
     * \param mediator The Mediator object used for managing the SDL context or related systems.
     */
	Font(const Asset & src, Mediator & mediator);
	/**
     * \brief Gets the underlying TTF_Font resource.
     * 
     * This function returns the raw pointer to the SDL_ttf TTF_Font object that represents
     * the loaded font. This can be used with SDL_ttf functions to render text.
     * 
     * \return The raw TTF_Font object wrapped in a unique pointer.
     */
	TTF_Font * get_font() const;

private:
	//! The SDL_ttf font object with custom deleter.
	std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> font = nullptr;
};

} // namespace crepe
