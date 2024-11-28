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
	/**
	 * \brief Constructs a Camera with the specified ID and background color.
	 * \param id Unique identifier for the camera component.
	 * \param bg_color Background color for the camera view.
	 */
	Camera(game_object_id_t id, const Color & bg_color, const ivec2 & screen,
		   const vec2 & viewport_size, const double & zoom, const vec2 & offset = {0, 0});
	~Camera(); // dbg_trace only

public:
	//! Background color of the camera view.
	const Color bg_color;

	//! offset postion from the game object transform component
	vec2 offset;

	//! screen the display size in pixels ( output resolution )
	const ivec2 screen;

	//! viewport is the area of the world visible through the camera (in world units)
	const vec2 viewport_size;

	//! Zoom level of the camera view.
	const double zoom;

public:
	/**
	 * \brief Gets the maximum number of camera instances allowed.
	 * \return Maximum instance count as an integer.
	 */
	virtual int get_instances_max() const { return 1; }
};
} // namespace crepe
