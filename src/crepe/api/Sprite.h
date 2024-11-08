#pragma once

#include <cstdint>
#include <memory>

#include "api/Color.h"
#include "api/Texture.h"

#include "Component.h"

namespace crepe {

/**
 * \struct Rect
 * \brief Represents a rectangle area for rendering.
 *
 * Everything within the defined rectangle will be rendered.
 * The SDLContext will translate this into the library's rectangle structure.
 */
struct Rect {
	int w = 0;
	int h = 0; 
	int x = 0; 
	int y = 0; 
};

/**
 * \struct FlipSettings
 * \brief Flip settings for the sprite.
 *
 * Defines the horizontal and vertical flip settings for a sprite, which the
 * SDLContext will translate into the corresponding settings for the library.
 */
struct FlipSettings {
	bool flip_x = false; 
	bool flip_y = false; 
};

//! Forward declaration of the SDLContext facade.
class SDLContext;

//! Forward declaration of the Animator class.
class Animator;

//! Forward declaration of the AnimatorSystem class.
class AnimatorSystem;

/**
 * \class Sprite
 * \brief Represents a renderable sprite component.
 *
 * A renderable sprite that can be displayed in the game. It includes a texture,
 * color, and flip settings, and is managed in layers with defined sorting orders.
 */
class Sprite : public Component {

public:
	/**
	 * \brief Constructs a Sprite with specified parameters.
	 * \param game_id Unique identifier for the game object this sprite belongs to.
	 * \param image Shared pointer to the texture for this sprite.
	 * \param color Color tint applied to the sprite.
	 * \param flip Flip settings for horizontal and vertical orientation.
	 */
	Sprite(game_object_id_t id, std::shared_ptr<Texture> image,
		   const Color & color, const FlipSettings & flip);

	/**
	 * \brief Destroys the Sprite instance.
	 */
	~Sprite();


	//! Texture used for the sprite
	std::shared_ptr<Texture> sprite_image;
	//! Color tint of the sprite 
	Color color;
	//! Flip settings for the sprite
	FlipSettings flip;
	//! Layer sorting level of the sprite
	uint8_t sorting_in_layer;
	//! Order within the sorting layer
	uint8_t order_in_layer;

public:
	/**
	 * \brief Gets the maximum number of instances allowed for this sprite.
	 * \return Maximum instance count as an integer.
	 */
	virtual int get_instances_max() const { return 10; }

private:
	friend class SDLContext;
	friend class Animator;
	friend class AnimatorSystem;

	//! Render area of the sprite
	Rect sprite_rect;
};

} // namespace crepe
