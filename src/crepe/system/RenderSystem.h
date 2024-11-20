#pragma once

#include <functional>
#include <vector>

#include "facade/SDLContext.h"

#include "System.h"

namespace crepe {

class Camera;
class Sprite;

/**
 * \class RenderSystem
 * \brief Manages rendering operations for all game objects.
 *
 * RenderSystem is responsible for rendering, clearing and presenting the screen, and
 * managing the active camera. 
 */
class RenderSystem : public System {
public:
	using System::System;
	/**
	 * \brief Updates the RenderSystem for the current frame.
	 * This method is called to perform all rendering operations for the current game frame.
	 */
	void update() override;

private:
	//! Clears the screen in preparation for rendering.
	void clear_screen();

	//! Presents the rendered frame to the display.
	void present_screen();

	//! Updates the active camera used for rendering.
	void update_camera();

	//! Renders all active sprites to the screen.
	void render_sprites();

	std::vector<std::reference_wrapper<Sprite>>
	sort(std::vector<std::reference_wrapper<Sprite>> & objs);

	/**
	 * \todo Include color handling for sprites.
	 * \todo Implement particle emitter rendering with sprites.
	 * \todo Add text rendering using SDL_ttf for text components.
	 * \todo Implement a text component and a button component.
	 * \todo Ensure each sprite is checked for active status before rendering.
	 * \todo Sort all layers by order before rendering.
	 * \todo Consider adding text input functionality.
	 */

private:
	//! Pointer to the current active camera for rendering
	Camera * curr_cam_ref = nullptr;
	// TODO: needs a better solution

	SDLContext & context = SDLContext::get_instance();
};

} // namespace crepe
