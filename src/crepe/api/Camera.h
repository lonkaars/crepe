#pragma once

#include "Color.h"
#include "Component.h"

#include "api/Config.h"
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
	Camera(game_object_id_t id, const Color & bg_color);
	~Camera(); // dbg_trace only

public:
	//! Background color of the camera view.
	Color bg_color;

	//! pos The position of the camera in world units
	vec2 pos = Config::get_instance().win_set.pos;

	//! screen the display size in pixels ( output resolution )
	vec2 screen = Config::get_instance().win_set.def_size;

	//! viewport is the area of the world visible through the camera (in world units)
	vec2 viewport = Config::get_instance().win_set.def_size;

	//! scale scaling factor from world units to pixel coordinates
	//! Zoom level of the camera view.
	double zoom = Config::get_instance().win_set.zoom;

public:
	/**
	 * \brief Gets the maximum number of camera instances allowed.
	 * \return Maximum instance count as an integer.
	 */
	virtual int get_instances_max() const { return 10; }
};
} // namespace crepe
