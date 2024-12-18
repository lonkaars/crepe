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
#include <unordered_map>

#include "../types.h"
#include "api/Camera.h"
#include "api/Color.h"
#include "api/KeyCodes.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include "types.h"

#include "EventData.h"
#include "FontFacade.h"

namespace crepe {
class Texture;
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

public:
	/**
	 * \brief Gets the singleton instance of SDLContext.
	 * \return Reference to the SDLContext instance.
	 */
	static SDLContext & get_instance();

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
	std::vector<EventData> get_events();
	/**
	 * \brief Fills event_list with triggered window events
	 *
	 * This method checks if any window events are triggered and adds them to the event_list.
	 *
	 */
	void handle_window_event(const SDL_WindowEvent & window_event,
							 std::vector<EventData> & event_list);
	/**
	 * \brief Converts an SDL scan code to the custom Keycode type.
	 *
	 * This method maps an SDL scan code to the corresponding `Keycode` enum value,
	 * which is used internally by the system to identify the keys.
	 *
	 * \param sdl_key The SDL scan code to convert.
	 * \return The corresponding `Keycode` value or `Keycode::NONE` if the key is unrecognized.
	 */
	Keycode sdl_to_keycode(SDL_Scancode sdl_key);

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
	/**
	 * \brief Gets the current state of the keyboard.
	 *
	 * Updates the internal keyboard state by checking the current key states using
	 * SDL's `SDL_GetKeyboardState()`, and returns a reference to the `keyboard_state_t`.
	 *
	 * \return A constant reference to the `keyboard_state_t`, which holds the state
	 *         of each key (true = pressed, false = not pressed).
	 */
	const keyboard_state_t & get_keyboard_state();

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
	//! variable to store the state of each key (true = pressed, false = not pressed)
	keyboard_state_t keyboard_state;
	//! lookup table for converting SDL_SCANCODES to Keycodes
	const std::unordered_map<SDL_Scancode, Keycode> lookup_table
		= {{SDL_SCANCODE_SPACE, Keycode::SPACE},
		   {SDL_SCANCODE_APOSTROPHE, Keycode::APOSTROPHE},
		   {SDL_SCANCODE_COMMA, Keycode::COMMA},
		   {SDL_SCANCODE_MINUS, Keycode::MINUS},
		   {SDL_SCANCODE_PERIOD, Keycode::PERIOD},
		   {SDL_SCANCODE_SLASH, Keycode::SLASH},
		   {SDL_SCANCODE_0, Keycode::D0},
		   {SDL_SCANCODE_1, Keycode::D1},
		   {SDL_SCANCODE_2, Keycode::D2},
		   {SDL_SCANCODE_3, Keycode::D3},
		   {SDL_SCANCODE_4, Keycode::D4},
		   {SDL_SCANCODE_5, Keycode::D5},
		   {SDL_SCANCODE_6, Keycode::D6},
		   {SDL_SCANCODE_7, Keycode::D7},
		   {SDL_SCANCODE_8, Keycode::D8},
		   {SDL_SCANCODE_9, Keycode::D9},
		   {SDL_SCANCODE_SEMICOLON, Keycode::SEMICOLON},
		   {SDL_SCANCODE_EQUALS, Keycode::EQUAL},
		   {SDL_SCANCODE_A, Keycode::A},
		   {SDL_SCANCODE_B, Keycode::B},
		   {SDL_SCANCODE_C, Keycode::C},
		   {SDL_SCANCODE_D, Keycode::D},
		   {SDL_SCANCODE_E, Keycode::E},
		   {SDL_SCANCODE_F, Keycode::F},
		   {SDL_SCANCODE_G, Keycode::G},
		   {SDL_SCANCODE_H, Keycode::H},
		   {SDL_SCANCODE_I, Keycode::I},
		   {SDL_SCANCODE_J, Keycode::J},
		   {SDL_SCANCODE_K, Keycode::K},
		   {SDL_SCANCODE_L, Keycode::L},
		   {SDL_SCANCODE_M, Keycode::M},
		   {SDL_SCANCODE_N, Keycode::N},
		   {SDL_SCANCODE_O, Keycode::O},
		   {SDL_SCANCODE_P, Keycode::P},
		   {SDL_SCANCODE_Q, Keycode::Q},
		   {SDL_SCANCODE_R, Keycode::R},
		   {SDL_SCANCODE_S, Keycode::S},
		   {SDL_SCANCODE_T, Keycode::T},
		   {SDL_SCANCODE_U, Keycode::U},
		   {SDL_SCANCODE_V, Keycode::V},
		   {SDL_SCANCODE_W, Keycode::W},
		   {SDL_SCANCODE_X, Keycode::X},
		   {SDL_SCANCODE_Y, Keycode::Y},
		   {SDL_SCANCODE_Z, Keycode::Z},
		   {SDL_SCANCODE_LEFTBRACKET, Keycode::LEFT_BRACKET},
		   {SDL_SCANCODE_BACKSLASH, Keycode::BACKSLASH},
		   {SDL_SCANCODE_RIGHTBRACKET, Keycode::RIGHT_BRACKET},
		   {SDL_SCANCODE_GRAVE, Keycode::GRAVE_ACCENT},
		   {SDL_SCANCODE_ESCAPE, Keycode::ESCAPE},
		   {SDL_SCANCODE_RETURN, Keycode::ENTER},
		   {SDL_SCANCODE_TAB, Keycode::TAB},
		   {SDL_SCANCODE_BACKSPACE, Keycode::BACKSPACE},
		   {SDL_SCANCODE_INSERT, Keycode::INSERT},
		   {SDL_SCANCODE_DELETE, Keycode::DELETE},
		   {SDL_SCANCODE_RIGHT, Keycode::RIGHT},
		   {SDL_SCANCODE_LEFT, Keycode::LEFT},
		   {SDL_SCANCODE_DOWN, Keycode::DOWN},
		   {SDL_SCANCODE_UP, Keycode::UP},
		   {SDL_SCANCODE_PAGEUP, Keycode::PAGE_UP},
		   {SDL_SCANCODE_PAGEDOWN, Keycode::PAGE_DOWN},
		   {SDL_SCANCODE_HOME, Keycode::HOME},
		   {SDL_SCANCODE_END, Keycode::END},
		   {SDL_SCANCODE_CAPSLOCK, Keycode::CAPS_LOCK},
		   {SDL_SCANCODE_SCROLLLOCK, Keycode::SCROLL_LOCK},
		   {SDL_SCANCODE_NUMLOCKCLEAR, Keycode::NUM_LOCK},
		   {SDL_SCANCODE_PRINTSCREEN, Keycode::PRINT_SCREEN},
		   {SDL_SCANCODE_PAUSE, Keycode::PAUSE},
		   {SDL_SCANCODE_F1, Keycode::F1},
		   {SDL_SCANCODE_F2, Keycode::F2},
		   {SDL_SCANCODE_F3, Keycode::F3},
		   {SDL_SCANCODE_F4, Keycode::F4},
		   {SDL_SCANCODE_F5, Keycode::F5},
		   {SDL_SCANCODE_F6, Keycode::F6},
		   {SDL_SCANCODE_F7, Keycode::F7},
		   {SDL_SCANCODE_F8, Keycode::F8},
		   {SDL_SCANCODE_F9, Keycode::F9},
		   {SDL_SCANCODE_F10, Keycode::F10},
		   {SDL_SCANCODE_F11, Keycode::F11},
		   {SDL_SCANCODE_F12, Keycode::F12},
		   {SDL_SCANCODE_KP_0, Keycode::KP0},
		   {SDL_SCANCODE_KP_1, Keycode::KP1},
		   {SDL_SCANCODE_KP_2, Keycode::KP2},
		   {SDL_SCANCODE_KP_3, Keycode::KP3},
		   {SDL_SCANCODE_KP_4, Keycode::KP4},
		   {SDL_SCANCODE_KP_5, Keycode::KP5},
		   {SDL_SCANCODE_KP_6, Keycode::KP6},
		   {SDL_SCANCODE_KP_7, Keycode::KP7},
		   {SDL_SCANCODE_KP_8, Keycode::KP8},
		   {SDL_SCANCODE_KP_9, Keycode::KP9},
		   {SDL_SCANCODE_LSHIFT, Keycode::LEFT_SHIFT},
		   {SDL_SCANCODE_LCTRL, Keycode::LEFT_CONTROL},
		   {SDL_SCANCODE_LALT, Keycode::LEFT_ALT},
		   {SDL_SCANCODE_LGUI, Keycode::LEFT_SUPER},
		   {SDL_SCANCODE_RSHIFT, Keycode::RIGHT_SHIFT},
		   {SDL_SCANCODE_RCTRL, Keycode::RIGHT_CONTROL},
		   {SDL_SCANCODE_RALT, Keycode::RIGHT_ALT},
		   {SDL_SCANCODE_RGUI, Keycode::RIGHT_SUPER},
		   {SDL_SCANCODE_MENU, Keycode::MENU}};
};

} // namespace crepe
