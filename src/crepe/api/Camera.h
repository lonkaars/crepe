#pragma once

#include "Color.h"
#include "Component.h"
#include "types.h"

namespace crepe {

/**
 * \class Camera
 * \brief Represents a camera component for rendering in the game.
 *
 * The Camera class defines the view parameters, including background color, aspect ratio,
 * position, and zoom level. It controls what part of the game world is visible on the screen.
 */
class Camera : public Component {
public:
	struct Data {
		/**
		 * \bg_color background color of the game
		 *
		 * This will make the background the same color as the given value.
		 */
		const Color bg_color = Color::BLACK;

		/**
		 * \zoom Zooming level of the game
		 *
		 * zoom = 1 --> no zoom.
		 * zoom < 1 --> zoom out
		 * zoom > 1 --> zoom in
		 */
		float zoom = 1.0;

		//! offset postion from the game object transform component
		vec2 postion_offset;
	};

public:
	/**
	 * \brief Constructs a Camera with the specified ID and background color.
	 * \param id Unique identifier for the camera component.
	 * \param viewport_size is the view of the world in game units
	 * \param data the camera component data
	 */
	Camera(game_object_id_t id, const vec2 & viewport_size, const Data & data);
	~Camera(); // dbg_trace only

public:
	Data data;

	//! viewport is the area of the world visible through the camera (in world units)
	const vec2 viewport_size;

public:
	/**
	 * \brief Gets the maximum number of camera instances allowed.
	 * \return Maximum instance count as an integer.
	 */
	virtual int get_instances_max() const { return 1; }
};
} // namespace crepe
