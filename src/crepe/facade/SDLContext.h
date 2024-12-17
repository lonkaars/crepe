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

#include "api/Camera.h"
#include "api/Color.h"
#include "api/KeyCodes.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include "types.h"

#include "FontFacade.h"

namespace crepe {

class Texture;
class Text;
class Font;
class Mediator;

/**
 * \brief Facade for the SDL library
 *
 * SDLContext is a singleton that handles the SDL window and renderer, provides methods for
 * event handling, and rendering to the screen. It is never used directly by the user
 */
class SDLContext {
public:
	//! data that the camera component cannot hold
	struct CameraAuxiliaryData {

		//! zoomed in viewport in game_units
		vec2 zoomed_viewport;

		/**
		 * \brief scaling factor
		 *
		 * depending on the black bars type will the scaling be different.
		 * - letterboxing --> scaling on the y-as
		 * - pillarboxing --> scaling on the x-as
		 */
		vec2 render_scale;

		/**
		 * \brief size of calculated black bars
		 *
		 * depending on the black bars type will the size be different
		 * - lettorboxing --> {0, bar_height}
		 * - pillarboxing --> {bar_width , 0}
		 */
		vec2 bar_size;

		//! Calculated camera position
		vec2 cam_pos;
	};

	//! rendering data needed to render on screen
	struct RenderContext {
		const Sprite & sprite;
		const Texture & texture;
		const vec2 & pos;
		const double & angle;
		const double & scale;
	};

	struct RenderText {
		const Text & text;
		const Font & font;
		const Transform & transform;
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

public:
	SDLContext(const SDLContext &) = delete;
	SDLContext(SDLContext &&) = delete;
	SDLContext & operator=(const SDLContext &) = delete;
	SDLContext & operator=(SDLContext &&) = delete;

public:
	/**
	 * \brief Constructs an SDLContext instance.
	 * Initializes SDL, creates a window and renderer.
	 */
	SDLContext(Mediator & mediator);

	/**
	 * \brief Destroys the SDLContext instance.
	 * Cleans up SDL resources, including the window and renderer.
	 */
	~SDLContext();

public:
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

public:
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

public:
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
	 * \return Width and height of the texture as an integer in pixels.
	 */
	ivec2 get_size(const Texture & ctx);

public:
	/**
	 * \brief Draws a sprite to the screen using the specified transform and camera.
	 * \param RenderContext Reference to rendering data to draw
	 */
	void draw(const RenderContext & ctx);

	/**
	 * \brief draws a text to the screen 
	 *
	 * \param data Reference to the rendering data needed to draw
	 */
	void draw_text(const RenderText & data);

	//! Clears the screen, preparing for a new frame.
	void clear_screen();

	//! Presents the rendered frame to the screen.
	void present_screen();

	/**
	 * \brief calculates camera view settings. such as black_bars, zoomed_viewport, scaling and
	 * adjusting window size.
	 *
	 * \note only supports windowed mode.
	 * \param camera Reference to the current Camera object in the scene.
	 * \param new_pos new camera position from transform and offset
	 */
	void update_camera_view(const Camera & camera, const vec2 & new_pos);

public:
	//! the data needed to construct a sdl dst rectangle
	struct DestinationRectangleData {
		const Sprite & sprite;
		const Texture & texture;
		const vec2 & pos;
		const double & img_scale;
	};

	/**
	 * \brief calculates the sqaure size of the image for destination
	 *
	 * \param data needed to calculate a destination rectangle
	 * \return sdl rectangle to draw a dst image to draw on the screen
	 */
	SDL_FRect get_dst_rect(const DestinationRectangleData & data) const;
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

	//! black bars rectangle to draw
	SDL_FRect black_bars[2] = {};

	/**
	 * \cam_aux_data extra data that the component cannot hold.
	 *
	 * - this is defined in this class because get_events() needs this information aswell
	 */
	CameraAuxiliaryData cam_aux_data;

private:
	//! instance of the font_facade
	FontFacade font_facade{};

public:
	/**
	 * \brief Function to Get asset from font_family
	 * 
	 * This function uses the FontFacade function to convert a font_family to an asset.
	 * 
	 * \param font_family name of the font style that needs to be used (will return an asset with default font path of the font_family doesnt exist)
	 * 
	 * \return asset with the font style absolute path
	 */
	Asset get_font_from_name(const std::string & font_family);
};

} // namespace crepe
