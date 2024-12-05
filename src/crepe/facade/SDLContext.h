#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "api/Camera.h"
#include "api/Color.h"
#include "api/Event.h"
#include "api/KeyCodes.h"
#include "api/Sprite.h"
#include "api/Texture.h"
#include "api/Transform.h"
#include "types.h"

namespace crepe {

class LoopManager;
class InputSystem;
/**
 * \class SDLContext
 * \brief Facade for the SDL library
 * 
 * SDLContext is a singleton that handles the SDL window and renderer, provides methods for
 * event handling, and rendering to the screen. It is never used directly by the user
 */
class SDLContext {
public:
	struct RenderContext {
		const Sprite & sprite;
		const Camera & cam;
		const vec2 & cam_pos;
		const vec2 & pos;
		const double & angle;
		const double & scale;
	};

public:
	//! EventType enum for passing eventType
	enum EventType {
		NONE = 0,
		MOUSEDOWN,
		MOUSEUP,
		MOUSEMOVE,
		MOUSEWHEEL,
		KEYUP,
		KEYDOWN,
		SHUTDOWN,

	};
	//! EventData struct for passing event data from facade
	struct EventData {
		SDLContext::EventType event_type = SDLContext::EventType::NONE;
		Keycode key = Keycode::NONE;
		bool key_repeat = false;
		MouseButton mouse_button = MouseButton::NONE;
		ivec2 mouse_position = {-1, -1};
		int scroll_direction = -1;
		float scroll_delta = INFINITY;
		ivec2 rel_mouse_move = {-1, -1};
	};
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
	//! will only use get_events
	friend class InputSystem;
	/**
	 * \brief Retrieves a list of all events from the SDL context.
	 * 
	 * This method retrieves all the events from the SDL context that are currently
	 * available. It is primarily used by the InputSystem to process various
	 * input events such as mouse clicks, mouse movements, and keyboard presses.
	 * 
	 * \return Events that occurred since last call to `get_events()`
	 */
	std::vector<SDLContext::EventData> get_events();

	/**
	 * \brief Converts an SDL key code to the custom Keycode type.
	 * 
	 * This method maps an SDL key code to the corresponding `Keycode` enum value,
	 * which is used internally by the system to identify the keys.
	 * 
	 * \param sdl_key The SDL key code to convert.
	 * \return The corresponding `Keycode` value or `Keycode::NONE` if the key is unrecognized.
	 */
	Keycode sdl_to_keycode(SDL_Keycode sdl_key);

	/**
	 * \brief Converts an SDL mouse button code to the custom MouseButton type.
	 * 
	 * This method maps an SDL mouse button code to the corresponding `MouseButton` 
	 * enum value, which is used internally by the system to identify mouse buttons.
	 * 
	 * \param sdl_button The SDL mouse button code to convert.
	 * \return The corresponding `MouseButton` value or `MouseButton::NONE` if the key is unrecognized
	 */
	MouseButton sdl_to_mousebutton(Uint8 sdl_button);

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

	/**
	 * \brief Loads a texture from a file path.
	 * \param path Path to the image file.
	 * \return Pointer to the created SDL_Texture.
	 */
	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>
	texture_from_path(const std::string & path);
	/**
	 * \brief Gets the size of a texture.
	 * \param texture Reference to the Texture object.
	 * \return Width and height of the texture as an integer.
	 */
	ivec2 get_size(const Texture & ctx);

private:
	//! Will use draw,clear_screen, present_screen, camera.
	friend class RenderSystem;

	/**
	 * \brief Draws a sprite to the screen using the specified transform and camera.
	 * \param RenderCtx Reference to rendering data to draw
	 */
	void draw(const RenderContext & ctx);

	//! Clears the screen, preparing for a new frame.
	void clear_screen();

	//! Presents the rendered frame to the screen.
	void present_screen();

	/**
	 * \brief sets the background of the camera (will be adjusted in future PR)
	 * \param camera Reference to the Camera object.
	 */
	void set_camera(const Camera & camera);

private:
	/**
	 * \brief calculates the sqaure size of the image
	 *
	 * \param sprite Reference to the sprite to calculate the rectangle
	 * \return sdl rectangle to draw a src image
	 */
	SDL_Rect get_src_rect(const Sprite & sprite) const;

	/**
	 * \brief calculates the sqaure size of the image for destination
	 *
	 * \param sprite Reference to the sprite to calculate rectangle
	 * \param pos the pos in world units
	 * \param cam the camera of the current scene
	 * \param cam_pos the current postion of the camera
	 * \param img_scale the image multiplier for increasing img size 
	 * \return sdl rectangle to draw a dst image to draw on the screen
	 */
	SDL_Rect get_dst_rect(const Sprite & sprite, const vec2 & pos, const Camera & cam,
						  const vec2 & cam_pos, const double & img_scale) const;
	/**
	 * \brief Set an additional color value multiplied into render copy operations.
	 *
	 * \param  texture the given texture to adjust 
	 * \param  color the color data for the texture
	 */
	void set_color_texture(const Texture & texture, const Color & color);

private:
	//! sdl Window
	std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> game_window;

	//! renderer for the crepe engine
	std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer *)>> game_renderer;
};

} // namespace crepe
