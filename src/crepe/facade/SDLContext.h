#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "api/Camera.h"

//FIXME: this needs to be removed
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

namespace crepe {
typedef SDL_Keycode CREPE_KEYCODES;

class Texture;
class LoopManager;

/**
 * \class SDLContext
 * \brief Facade for the SDL library
 * 
 * SDLContext is a singleton that handles the SDL window and renderer, provides methods
 * for event handling, and rendering to the screen. It is never used directly by the user
 */
class SDLContext {

public:
	/**
    * \brief Gets the singleton instance of SDLContext.
    * \return Reference to the SDLContext instance.
    */
	static SDLContext & get_instance();

	SDLContext(const SDLContext &) = delete;
	SDLContext(SDLContext &&) = delete;
	SDLContext & operator=(const SDLContext &) = delete;
	SDLContext & operator=(SDLContext &&) = delete;

private:
	//! will only use handle_events
	friend class LoopManager;
	/**
	* \brief Handles SDL events such as window close and input.
	* \param running Reference to a boolean flag that controls the main loop.
	*/
	void handle_events(bool & running);

private:
	//! Will only use get_ticks
	friend class AnimatorSystem;

	/**
	* \brief Gets the current SDL ticks since the program started.
	* \return Current ticks in milliseconds as a constant uint64_t.
	*/
	const uint64_t get_ticks() const;

private:
	/**
	* \brief Constructs an SDLContext instance.
	* Initializes SDL, creates a window and renderer.
	*/
	SDLContext();

	/**
	* \brief Destroys the SDLContext instance.
	* Cleans up SDL resources, including the window and renderer.
	*/
	~SDLContext();

private:
	//! Will use the funtions: texture_from_path, get_width,get_height.
	friend class Texture;

	//! Will use the funtions: texture_from_path, get_width,get_height.
	friend class Animator;

	/**
	* \brief Loads a texture from a file path.
    * \param path Path to the image file.
    * \return Pointer to the created SDL_Texture.
    */
	SDL_Texture * texture_from_path(const std::string & path);

	/**
    * \brief Gets the width of a texture.
    * \param texture Reference to the Texture object.
    * \return Width of the texture as an integer.
    */
	int get_width(const Texture &) const;

	/**
    * \brief Gets the height of a texture.
    * \param texture Reference to the Texture object.
    * \return Height of the texture as an integer.
    */
	int get_height(const Texture &) const;

private:
	//! Will use draw,clear_screen, present_screen, camera.
	friend class RenderSystem;

	/**
    * \brief Draws a sprite to the screen using the specified transform and camera.
    * \param sprite Reference to the Sprite to draw.
    * \param transform Reference to the Transform for positioning.
    * \param camera Reference to the Camera for view adjustments.
    */
	void draw(const Sprite & sprite, const Transform & transform,
			  const Camera & camera);

	/**
    * \brief Clears the screen, preparing for a new frame.
         */
	void clear_screen();

	/**
    * \brief Presents the rendered frame to the screen.
    */
	void present_screen();

	/**
	* \brief Sets the current camera for rendering.
    * \param camera Reference to the Camera object.
    */
	void camera(const Camera & camera);

private:
	//TODO: Make this RAII
	//! sdl window
	SDL_Window * game_window = nullptr;
	//! renderer for the crepe engine
	SDL_Renderer * game_renderer = nullptr;

	//! viewport for the camera window
	SDL_Rect viewport = {0, 0, 640, 480};
};

} // namespace crepe
