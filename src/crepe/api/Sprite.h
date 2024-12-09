#pragma once

#include "../Component.h"
#include "api/Asset.h"

#include "Color.h"
#include "types.h"

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
	//! settings to flip the image
	struct FlipSettings {
		//! horizantal flip
		bool flip_x = false;
		//! vertical flip
		bool flip_y = false;
	};

	//! Sprite data that does not have to be set in the constructor
	struct Data {
		/**
		 * \brief Sprite tint (multiplied)
		 *
		 * The sprite texture's pixels are multiplied by this color before being displayed
		 * (including alpha channel for transparency).
		 */
		Color color = Color::WHITE;

		//! Flip settings for the sprite
		FlipSettings flip;

		//! Layer sorting level of the sprite
		const int sorting_in_layer = 0;

		//! Order within the sorting layer
		const int order_in_layer = 0;

		/**
		 * \brief width and height of the sprite in game units
		 *
		 * - if exclusively width is specified, the height is calculated using the texture's aspect
		 *   ratio
		 * - if exclusively height is specified, the width is calculated using the texture's aspect
		 *   ratio
		 * - if both are specified the texture is streched to fit the specified size
		 */
		vec2 size = {0, 0};

		//! independent sprite angle. rotating clockwise direction in degrees
		float angle_offset = 0;

		//! independent sprite scale multiplier
		float scale_offset = 1;

		//! independent sprite offset position
		vec2 position_offset;
	};

public:
	/**
	 * \param game_id Unique identifier for the game object this sprite belongs to.
	 * \param texture asset of the image
	 * \param ctx all the sprite data
	 */
	Sprite(game_object_id_t id, const Asset & texture, const Data & data);
	~Sprite();

	//! Texture used for the sprite
	const Asset source;

	Data data;

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
