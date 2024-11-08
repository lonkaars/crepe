#pragma once

// FIXME: this header can't be included because this is an API header, and SDL2
// development headers won't be bundled with crepe. Why is this facade in the
// API namespace?

#include <SDL2/SDL_render.h>
#include <memory>

#include "Asset.h"

namespace crepe {

//! Forward declaration of SDLContext class.
class SDLContext;

//! Forward declaration of Animator class.
class Animator;

/**
 * \class Texture
 * \brief Manages texture loading and properties.
 *
 * The Texture class is responsible for loading an image from a source
 * and providing access to its dimensions. Textures can be used for rendering.
 */
class Texture {

public:
    /**
     * \brief Constructs a Texture from a file path.
     * \param src Path to the image file to be loaded as a texture.
     */
    Texture(const char * src);

    /**
     * \brief Constructs a Texture from an Asset resource.
     * \param res Unique pointer to an Asset resource containing texture data.
     */
    Texture(std::unique_ptr<Asset> res);

    /**
     * \brief Destroys the Texture instance, freeing associated resources.
     */
    ~Texture();

    /**
     * \brief Gets the width of the texture.
     * \return Width of the texture in pixels.
     */
    int get_width() const;

    /**
     * \brief Gets the height of the texture.
     * \return Height of the texture in pixels.
     */
    int get_height() const;

private:
    /**
     * \brief Loads the texture from an Asset resource.
     * \param res Unique pointer to an Asset resource to load the texture from.
     */
    void load(std::unique_ptr<Asset> res);

private:
	//TODO make RAII
	//! The texture of the class from the library
    SDL_Texture * texture = nullptr; 

    //! Grants SDLContext access to private members.
    friend class SDLContext;

    //! Grants Animator access to private members.
    friend class Animator;
};

} // namespace crepe
