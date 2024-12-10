#pragma once

// FIXME: this header can't be included because this is an API header, and SDL2 development
// headers won't be bundled with crepe. Why is this facade in the API namespace?

#include <SDL2/SDL_render.h>
#include <memory>

#include "../Resource.h"

#include "types.h"

namespace crepe {

class Mediator;
class Asset;

/**
 * \class Texture
 * \brief Manages texture loading and properties.
 *
 * The Texture class is responsible for loading an image from a source and providing access to
 * its dimensions. Textures can be used for rendering.
 */
class Texture : public Resource {

public:
	/**
	 * \brief Constructs a Texture from an Asset resource.
	 * \param src Asset with texture data to load.
	 * \param mediator use the SDLContext reference to load the image
	 */
	Texture(const Asset & src, Mediator & mediator);

	/**
	 * \brief Destroys the Texture instance
	 */
	~Texture();

	/**
	 * \brief get width and height of image in pixels
	 * \return pixel size width and height
	 *
	 */
	const ivec2 & get_size() const noexcept;

	/**
	 * \brief aspect_ratio of image
	 * \return ratio
	 *
	 */
	const float & get_ratio() const noexcept;

	/**
	 * \brief get the image texture
	 * \return SDL_Texture
	 *
	 */
	SDL_Texture * get_img() const noexcept;

private:
	//! The texture of the class from the library
	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> texture;

	// texture size in pixel
	ivec2 size;

	//! ratio of image
	float aspect_ratio;
};

} // namespace crepe
