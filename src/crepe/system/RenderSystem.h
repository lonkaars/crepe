#pragma once

#include "System.h"
#include "api/Camera.h"

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
    /**
     * \brief Constructs a RenderSystem instance.
     * Private constructor to enforce singleton pattern.
     */
    RenderSystem();

    /**
     * \brief Destroys the RenderSystem instance.
     */
    ~RenderSystem();

    /**
     * \brief Clears the screen in preparation for rendering.
     */
    void clear_screen();

    /**
     * \brief Presents the rendered frame to the display.
     */
    void present_screen();

    /**
     * \brief Updates the active camera used for rendering.
     */
    void update_camera();

    /**
     * \brief Renders all active sprites to the screen.
     */
    void render_sprites();

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
	// \todo needs a better solution
    Camera * curr_cam; 
};
} // namespace crepe
