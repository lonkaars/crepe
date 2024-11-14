#pragma once

#include "api/Camera.h"
#include "api/Sprite.h"
#include "api/Transform.h"

#include "System.h"

namespace crepe {

/**
 * \class RenderSystem
 * \brief Manages rendering operations for all game objects.
 *
 * RenderSystem is responsible for rendering sprites, clearing and presenting the screen, 
 * and managing the active camera. It functions as a singleton, providing centralized 
 * rendering services for the application.
 */
class RenderSystem : public System {

public:
	/**
	 * \brief Gets the singleton instance of RenderSystem.
	 * \return Reference to the RenderSystem instance.
	 */
	static RenderSystem & get_instance();

	/**
	 * \brief Updates the RenderSystem for the current frame.
	 * This method is called to perform all rendering operations for the current game frame.
	 */
	void update() override;

private:
	// Private constructor to enforce singleton pattern.
	RenderSystem();
	~RenderSystem();

	//! Clears the screen in preparation for rendering.
	void clear_screen() const;

	//! Presents the rendered frame to the display.
	void present_screen() const;

	//! Updates the active camera used for rendering.
	void update_camera();

	//! Renders the whole screen
	void render();

	/**
	 * \brief Renders all the particles on the screen from a given sprite.
	 *
	 * \param sprite renders the particles with given texture
	 * \param tm the Transform component for scale
	 * \return true if particles have been rendered
	 */
	bool render_particle(const Sprite &, const Transform & tm);

	/**
	 * \brief renders a sprite with a Transform component on the screen 
	 *
	 * \param sprite  the sprite component that holds all the data
	 * \param tm the Transform component that holds the position,rotation and scale 
	 */
	void render_normal(const Sprite &, const Transform & tm);

	/**
	 * \todo Include color handling for sprites.
	 * \todo Add text rendering using SDL_ttf for text components.
	 * \todo Implement a text component and a button component.
	 * \todo Ensure each sprite is checked for active status before rendering.
	 * \todo Sort all layers by order before rendering.
	 * \todo Consider adding text input functionality.
	 */

private:
	//! Pointer to the current active camera for rendering
	Camera * curr_cam = nullptr;
	// TODO: needs a better solution
};
} // namespace crepe
