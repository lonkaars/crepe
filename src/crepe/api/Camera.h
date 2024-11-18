#pragma once

#include "Color.h"
#include "Component.h"
#include "api/Vector2.h"

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

	Vector2 pos = {0,0};

	Vector2 screen = {640,480};

	Vector2 viewport = {500,500};

	/*
	//! screen width in pixel coordinates
	double screen_w = 480;

	//! screen height in pixel coordinates
	double screen_h = 640;

	//! screen widht in world units
	double viewport_w = 500.0f;
	
	//! screen height in world units 
	double viewport_h = 500.0f;

	//! X-coordinate of the camera position. in world space
	double x = 0.0;

	//! Y-coordinate of the camera position. in world space
	double y = 0.0;

	*/

	//! Zoom level of the camera view.
	double zoom = 1.0f;

public:
	/**
	 * \brief Gets the maximum number of camera instances allowed.
	 * \return Maximum instance count as an integer.
	 */
	virtual int get_instances_max() const { return 10; }
};
} // namespace crepe
