#pragma once

#include <cstdint>

#include "Color.h"
#include "Component.h"

namespace crepe {

/**
 * \class Camera
 * \brief Represents a camera component for rendering in the game.
 *
 * The Camera class defines the view parameters, including background color, 
 * aspect ratio, position, and zoom level. It controls what part of the game 
 * world is visible on the screen.
 */
class Camera : public Component {

public:
	/**
	 * \brief Constructs a Camera with the specified ID and background color.
	 * \param id Unique identifier for the camera component.
	 * \param bg_color Background color for the camera view.
	 */
	Camera(const Component::Data & data, const Color & bg_color);
	~Camera(); // dbg_trace only

public:
	//! Background color of the camera view.
	Color bg_color;

	//! Aspect ratio height for the camera.
	double aspect_height = 480;

	//! Aspect ratio width for the camera.
	double aspect_width = 640;

	//! X-coordinate of the camera position.
	double x = 0.0;

	//! Y-coordinate of the camera position.
	double y = 0.0;

	//! Zoom level of the camera view.
	double zoom = 1.0;

public:
	/**
	 * \brief Gets the maximum number of camera instances allowed.
	 * \return Maximum instance count as an integer.
	 */
	virtual int get_instances_max() const { return 10; }
};
} // namespace crepe
