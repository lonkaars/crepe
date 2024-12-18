#pragma once

#include <cmath>

#include "System.h"
#include "types.h"

namespace crepe {

class Camera;
class Sprite;
class Transform;
class Text;
/**
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

	//! Renders all the sprites and particles
	void render();

	//! Renders all Text components
	void render_text();

private:
	/**
	 * \brief Renders all the particles on the screen from a given sprite.
	 *
	 * \param sprite renders the particles with given texture
	 * \param tm the Transform component for scale. This is not a const reference because each
	 *  particle has a position and rotation that needs to overwrite the transform position and
	 *  rotation without overwriting the current transform. and because the transform
	 *  constructor is now protected i cannot make tmp inside
	 * \return true if particles have been rendered
	 */
	bool render_particle(const Sprite & sprite, const Transform & tm);
	/**
	 * \brief renders a sprite with a Transform component on the screen
	 *
	 * \param sprite  the sprite component that holds all the data
	 * \param tm the Transform component that holds the position,rotation and scale
	 */
	void render_normal(const Sprite & sprite, const Transform & tm);

	/**
	 * \brief sort a vector sprite objects with
	 *
	 * \param objs the vector that will do a sorting algorithm on
	 * \return returns a sorted reference vector
	 */
	RefVector<Sprite> sort(RefVector<Sprite> & objs) const;

	/**
	 * \todo Add text rendering using SDL_ttf for text components.
	 * \todo Implement a text component and a button component.
	 * \todo Consider adding text input functionality.
	 */
};

} // namespace crepe
