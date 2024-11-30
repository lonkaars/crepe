#pragma once

#include <cstdint>

#include "../Component.h"

#include "Color.h"
#include "Texture.h"

namespace crepe {

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
	struct FlipSettings {
		bool flip_x = false;
		bool flip_y = false;
	};

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
	Sprite(game_object_id_t id, Texture & image, const Color & color,
		   const FlipSettings & flip, int sort_layer, int order_layer, float height);

	/**
	 * \brief Destroys the Sprite instance.
	 */
	~Sprite();

	//! Texture used for the sprite
	const Texture sprite_image;

	//! Color tint of the sprite
	Color color;

	//! Flip settings for the sprite
	FlipSettings flip;

	//! Layer sorting level of the sprite
	const int sorting_in_layer;
	//! Order within the sorting layer
	const int order_in_layer;

	//! height in world units
	const float height;

	/**
	 * \aspect_ratio ratio of the img so that scaling will not become weird
	 *
	 * cannot be const because if Animator component is addded then ratio becomes scuffed and
	 * does it need to be calculated again in the Animator
	 */
	float aspect_ratio;

private:
	//! Reads the mask of sprite
	friend class SDLContext;

	//! Reads the all the variables plus the  mask
	friend class Animator;

	//! Reads the all the variables plus the  mask
	friend class AnimatorSystem;

	struct Rect {
		int w = 0;
		int h = 0;
		int x = 0;
		int y = 0;
	};
	//! Render area of the sprite this will also be adjusted by the AnimatorSystem if an Animator
	// object is present in GameObject. this is in sprite pixels
	Rect mask;
};

} // namespace crepe
