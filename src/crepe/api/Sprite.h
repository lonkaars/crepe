#pragma once

#include <memory>

#include "../Component.h"

#include "Color.h"
#include "Texture.h"

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
	 */
	Sprite(game_object_id_t id, const std::shared_ptr<Texture> image, const Color & color,
		   const FlipSettings & flip);

	/**
	 * \brief Destroys the Sprite instance.
	 */
	~Sprite();

	//! Texture used for the sprite
	const std::shared_ptr<Texture> sprite_image;
	//! Color tint of the sprite
	Color color;
	//! Flip settings for the sprite
	FlipSettings flip;
	//! Layer sorting level of the sprite
	uint8_t sorting_in_layer = 0;
	//! Order within the sorting layer
	uint8_t order_in_layer = 0;

public:
	/**
	 * \brief Gets the maximum number of instances allowed for this sprite.
	 * \return Maximum instance count as an integer.
	 *
	 * For now is this number randomly picked. I think it will eventually be 1. 
	 */
	virtual int get_instances_max() const { return 10; }

private:
	//! Reads the sprite_rect of sprite
	friend class SDLContext;

	//! Reads the all the variables plus the  sprite_rect
	friend class Animator;

	//! Reads the all the variables plus the  sprite_rect
	friend class AnimatorSystem;

	//! Render area of the sprite this will also be adjusted by the AnimatorSystem if an Animator
	// object is present in GameObject
	Rect sprite_rect;
};

} // namespace crepe
