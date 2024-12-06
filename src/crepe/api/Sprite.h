#pragma once

#include "../Component.h"

#include "Color.h"
#include "Texture.h"
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

	struct Data {
		//! Color tint of the sprite
		Color color = Color::WHITE;

		//! Flip settings for the sprite
		FlipSettings flip;

		//! Layer sorting level of the sprite
		const int sorting_in_layer = 0;

		//! Order within the sorting layer
		const int order_in_layer = 0;

		/**
	 	* \size width and height of the sprite in game units
	 	*
	 	* if height is filled in and not width it will multiply width by aspect_ratio.
	 	* if width is filled in and not height it will multiply height by aspect_ratio.
	 	* if neither is filled it will not show sprite because size will be zero
	 	* if both are filled will it use the width and height without making sure the aspect_ratio
	 	* is correct
	 	*/
		vec2 size;

		//! independent sprite angle. rotating clockwise direction in degrees
		float angle_offset = 0;

		//! independent sprite scale multiplier
		float scale_offset = 1;

		//! independent sprite offset position
		vec2 position_offset;
	};

public:
	/**
	 * \brief Constructs a Sprite with specified parameters.
	 * \param game_id Unique identifier for the game object this sprite belongs to.
	 * \param texture asset of the image
	 * \param ctx all the sprite data
	 */
	Sprite(game_object_id_t id, Texture & texture, const Data & ctx);
	~Sprite();

	//! Texture used for the sprite
	const Texture texture;

	Data data;

private:
	/**
		* \aspect_ratio ratio of the img so that scaling will not become weird
		*
		* cannot be const because if Animator component is addded then ratio becomes scuffed and
		* does it need to be calculated again in the Animator
		*/
	float aspect_ratio;

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
