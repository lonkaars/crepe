#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <functional>
#include <memory>
#include <string>

#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "api/Camera.h"
#include "api/Vector2.h"

namespace crepe {

// TODO: SDL_Keycode is defined in a header not distributed with crepe, which means this
// typedef is unusable when crepe is packaged. Wouter will fix this later.
typedef SDL_Keycode CREPE_KEYCODES;

class Texture;
class LoopManager;

/**
 * \class SDLContext
 * \brief Facade for the SDL library
 * 
 * SDLContext is a singleton that handles the SDL window and renderer, provides methods for
 * event handling, and rendering to the screen. It is never used directly by the user
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
	//! Will only use delay
	friend class LoopTimer;
	/**
	 * \brief Gets the current SDL ticks since the program started.
	 * \return Current ticks in milliseconds as a constant uint64_t.
	 */
	uint64_t get_ticks() const;
	/**
	 * \brief Pauses the execution for a specified duration.
	 *
	 * This function uses SDL's delay function to halt the program execution for a given number
	 * of milliseconds, allowing for frame rate control or other timing-related functionality.
	 *
	 * \param ms Duration of the delay in milliseconds.
	 */
	void delay(int ms) const;

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
	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>
	texture_from_path(const std::string & path);
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
	void draw(const Sprite & sprite, const Transform & transform, const Camera & camera);
	void draw_particle(const Sprite & sprite, const Vector2 & pos, const double & angle, const double & scale, const Camera & camera);

	//! Clears the screen, preparing for a new frame.
	void clear_screen();

	//! Presents the rendered frame to the screen.
	void present_screen();

	/**
	 * \brief Sets the current camera for rendering.
	 * \param camera Reference to the Camera object.
	 */
	void camera(const Camera & camera);

private:
	/**
	 * \brief calculates the sqaure size of the image
	 *
	 * \param sprite Reference to the sprite to calculate the rectangle
	 * \return sdl rectangle to draw a src image
	 */
	SDL_Rect get_src_rect(const Sprite & sprite);
	/**
	 * \brief calculates the sqaure size of the image for an destination
	 *
	 * \param sprite Reference to the sprite to calculate the rectangle
	 * \param pos the pos in pixel positions
	 * \param scale the multiplier to increase of decrease for the specified sprite 
	 * \param cam Reference to the current camera in the scene to calculate the position based
	 * on the camera 
	 * \return sdl rectangle to draw a dst image to draw on the screen
	 */
	SDL_Rect get_dst_rect(const Sprite & sprite, const Vector2 & pos, const double & scale, const Camera & cam);

private:
	//! sdl Window
	std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> game_window;

	//! renderer for the crepe engine
	std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> game_renderer;

	//! viewport for the camera window
	SDL_Rect viewport = {0, 0, 640, 480};
};

} // namespace crepe
