#pragma once

#include <SDL2/SDL_ttf.h>
#include <functional>
#include <memory>

#include "Asset.h"

namespace crepe {

class SDLContext;

/**
 * \class Font
 * \brief Manages font loading and text rendering properties.
 *
 * The Font class is responsible for loading font resources and providing a way to render text
 * with different styles and sizes. It can be used for text rendering in the game engine.
 */
class Font {

public:
    /**
     * \brief Constructs a Font from an Asset resource.
     * \param src Asset with font data to load.
     * \param size The point size to render the font at.
     */
    Font(const Asset &src, int size);

    /**
     * \brief Destroys the Font instance, freeing associated resources.
     */
    ~Font();

    /**
     * \brief Gets the size of the font.
     * \return The point size of the font.
     */
    int get_size() const;

private:
    /**
     * \brief Loads the font from an Asset resource.
     * \param res The Asset resource containing the font data.
     * \param size The point size to render the font at.
     */
    void load(const Asset &res, int size);

private:
    //! The font resource from the SDL_ttf library.
    std::unique_ptr<TTF_Font, std::function<void(TTF_Font *)>> font;

    //! The size of the font in points.
    int font_size;

    //! Grants SDLContext access to private members.
    friend class SDLContext;
};

} // namespace crepe
