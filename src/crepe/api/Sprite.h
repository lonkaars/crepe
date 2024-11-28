#pragma once

#include "../Component.h"

#include "Color.h"
#include "Texture.h"
#include <cstdint>

namespace crepe {

struct Rect {
	int w = 0;
	int h = 0;
	int x = 0;
	int y = 0;
};

struct FlipSettings {
	bool flip_x = false;
	bool flip_y = false;
};

class SDLContext;
class Animator;
class AnimatorSystem;

/**
 * \brief Represents a renderable sprite component.
 *
 * A renderable sprite that can be displayed in the game. It includes a texture, color, and
 * flip settings, and is managed in layers with defined sorting orders.
 */
class Sprite : public Component {

public:
	// TODO: Loek comment in github #27 will be looked another time
	// about shared_ptr Texture
	/**
	 * \brief Constructs a Sprite with specified parameters.
	 * \param game_id Unique identifier for the game object this sprite belongs to.
	 * \param image Shared pointer to the texture for this sprite.
	 * \param color Color tint applied to the sprite.
	 * \param flip Flip settings for horizontal and vertical orientation.
	 * \param order_layer decides the sorting in layer of the sprite.
	 * \param sort_layer decides the order in layer of the sprite.
	 * \param height the height of the image in game units
	 */
	Sprite(game_object_id_t id, const Texture & image, const Color & color,
		   const FlipSettings & flip, uint8_t sort_layer, uint8_t order_layer, int height);

	/**
	 * \brief Destroys the Sprite instance.
	 */
	~Sprite();

	//! Texture used for the sprite
	const Texture & sprite_image;

	//! Color tint of the sprite
	Color color;

	//! Flip settings for the sprite
	FlipSettings flip;

	//! Layer sorting level of the sprite
	const uint8_t sorting_in_layer;
	//! Order within the sorting layer
	const uint8_t order_in_layer;

	//! height in world units
	const int height;

	/**
	 * \aspect_ratio ratio of the img so that scaling will not become weird
	 *
	 * cannot be const because if Animator component is addded then ratio becomes scuffed and
	 * does it need to be calculated again in the Animator
	 */
	double aspect_ratio;

private:
	//! Reads the sprite_rect of sprite
	friend class SDLContext;

	//! Reads the all the variables plus the  sprite_rect
	friend class Animator;

	//! Reads the all the variables plus the  sprite_rect
	friend class AnimatorSystem;

	//! Render area of the sprite this will also be adjusted by the AnimatorSystem if an Animator
	// object is present in GameObject. this is in sprite pixels
	Rect sprite_rect;
};

} // namespace crepe
