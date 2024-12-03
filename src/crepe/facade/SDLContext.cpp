#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../api/Camera.h"
#include "../api/Sprite.h"
#include "../api/Texture.h"
#include "../util/Log.h"

#include "SDLContext.h"
#include "api/Color.h"
#include "types.h"

using namespace crepe;
using namespace std;

SDLContext & SDLContext::get_instance() {
	static SDLContext instance;
	return instance;
}

SDLContext::SDLContext() {
	dbg_trace();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw runtime_error(format("SDLContext: SDL_Init error: {}", SDL_GetError()));
	}

	auto & cfg = Config::get_instance().window_settings;
	SDL_Window * tmp_window
		= SDL_CreateWindow(cfg.window_title.c_str(), SDL_WINDOWPOS_CENTERED,
						   SDL_WINDOWPOS_CENTERED, cfg.default_size.x, cfg.default_size.y, 0);
	if (!tmp_window) {
		throw runtime_error(format("SDLContext: SDL_Window error: {}", SDL_GetError()));
	}
	this->game_window = {tmp_window, [](SDL_Window * window) { SDL_DestroyWindow(window); }};

	SDL_Renderer * tmp_renderer
		= SDL_CreateRenderer(this->game_window.get(), -1, SDL_RENDERER_ACCELERATED);
	if (!tmp_renderer) {
		throw runtime_error(
			format("SDLContext: SDL_CreateRenderer error: {}", SDL_GetError()));
	}

	this->game_renderer
		= {tmp_renderer, [](SDL_Renderer * renderer) { SDL_DestroyRenderer(renderer); }};

	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		throw runtime_error("SDLContext: SDL_image could not initialize!");
	}
}

SDLContext::~SDLContext() {
	dbg_trace();

	this->game_renderer.reset();
	this->game_window.reset();

	// TODO: how are we going to ensure that these are called from the same
	// thread that SDL_Init() was called on? This has caused problems for me
	// before.
	IMG_Quit();
	SDL_Quit();
}

Keycode SDLContext::sdl_to_keycode(SDL_Keycode sdl_key) {
	static const std::array<Keycode, SDL_NUM_SCANCODES> LOOKUP_TABLE = [] {
		std::array<Keycode, SDL_NUM_SCANCODES> table{};
		table.fill(Keycode::NONE);

		table[SDL_SCANCODE_SPACE] = Keycode::SPACE;
		table[SDL_SCANCODE_APOSTROPHE] = Keycode::APOSTROPHE;
		table[SDL_SCANCODE_COMMA] = Keycode::COMMA;
		table[SDL_SCANCODE_MINUS] = Keycode::MINUS;
		table[SDL_SCANCODE_PERIOD] = Keycode::PERIOD;
		table[SDL_SCANCODE_SLASH] = Keycode::SLASH;
		table[SDL_SCANCODE_0] = Keycode::D0;
		table[SDL_SCANCODE_1] = Keycode::D1;
		table[SDL_SCANCODE_2] = Keycode::D2;
		table[SDL_SCANCODE_3] = Keycode::D3;
		table[SDL_SCANCODE_4] = Keycode::D4;
		table[SDL_SCANCODE_5] = Keycode::D5;
		table[SDL_SCANCODE_6] = Keycode::D6;
		table[SDL_SCANCODE_7] = Keycode::D7;
		table[SDL_SCANCODE_8] = Keycode::D8;
		table[SDL_SCANCODE_9] = Keycode::D9;
		table[SDL_SCANCODE_SEMICOLON] = Keycode::SEMICOLON;
		table[SDL_SCANCODE_EQUALS] = Keycode::EQUAL;
		table[SDL_SCANCODE_A] = Keycode::A;
		table[SDL_SCANCODE_B] = Keycode::B;
		table[SDL_SCANCODE_C] = Keycode::C;
		table[SDL_SCANCODE_D] = Keycode::D;
		table[SDL_SCANCODE_E] = Keycode::E;
		table[SDL_SCANCODE_F] = Keycode::F;
		table[SDL_SCANCODE_G] = Keycode::G;
		table[SDL_SCANCODE_H] = Keycode::H;
		table[SDL_SCANCODE_I] = Keycode::I;
		table[SDL_SCANCODE_J] = Keycode::J;
		table[SDL_SCANCODE_K] = Keycode::K;
		table[SDL_SCANCODE_L] = Keycode::L;
		table[SDL_SCANCODE_M] = Keycode::M;
		table[SDL_SCANCODE_N] = Keycode::N;
		table[SDL_SCANCODE_O] = Keycode::O;
		table[SDL_SCANCODE_P] = Keycode::P;
		table[SDL_SCANCODE_Q] = Keycode::Q;
		table[SDL_SCANCODE_R] = Keycode::R;
		table[SDL_SCANCODE_S] = Keycode::S;
		table[SDL_SCANCODE_T] = Keycode::T;
		table[SDL_SCANCODE_U] = Keycode::U;
		table[SDL_SCANCODE_V] = Keycode::V;
		table[SDL_SCANCODE_W] = Keycode::W;
		table[SDL_SCANCODE_X] = Keycode::X;
		table[SDL_SCANCODE_Y] = Keycode::Y;
		table[SDL_SCANCODE_Z] = Keycode::Z;
		table[SDL_SCANCODE_LEFTBRACKET] = Keycode::LEFT_BRACKET;
		table[SDL_SCANCODE_BACKSLASH] = Keycode::BACKSLASH;
		table[SDL_SCANCODE_RIGHTBRACKET] = Keycode::RIGHT_BRACKET;
		table[SDL_SCANCODE_GRAVE] = Keycode::GRAVE_ACCENT;
		table[SDL_SCANCODE_ESCAPE] = Keycode::ESCAPE;
		table[SDL_SCANCODE_RETURN] = Keycode::ENTER;
		table[SDL_SCANCODE_TAB] = Keycode::TAB;
		table[SDL_SCANCODE_BACKSPACE] = Keycode::BACKSPACE;
		table[SDL_SCANCODE_INSERT] = Keycode::INSERT;
		table[SDL_SCANCODE_DELETE] = Keycode::DELETE;
		table[SDL_SCANCODE_RIGHT] = Keycode::RIGHT;
		table[SDL_SCANCODE_LEFT] = Keycode::LEFT;
		table[SDL_SCANCODE_DOWN] = Keycode::DOWN;
		table[SDL_SCANCODE_UP] = Keycode::UP;
		table[SDL_SCANCODE_PAGEUP] = Keycode::PAGE_UP;
		table[SDL_SCANCODE_PAGEDOWN] = Keycode::PAGE_DOWN;
		table[SDL_SCANCODE_HOME] = Keycode::HOME;
		table[SDL_SCANCODE_END] = Keycode::END;
		table[SDL_SCANCODE_CAPSLOCK] = Keycode::CAPS_LOCK;
		table[SDL_SCANCODE_SCROLLLOCK] = Keycode::SCROLL_LOCK;
		table[SDL_SCANCODE_NUMLOCKCLEAR] = Keycode::NUM_LOCK;
		table[SDL_SCANCODE_PRINTSCREEN] = Keycode::PRINT_SCREEN;
		table[SDL_SCANCODE_PAUSE] = Keycode::PAUSE;
		table[SDL_SCANCODE_F1] = Keycode::F1;
		table[SDL_SCANCODE_F2] = Keycode::F2;
		table[SDL_SCANCODE_F3] = Keycode::F3;
		table[SDL_SCANCODE_F4] = Keycode::F4;
		table[SDL_SCANCODE_F5] = Keycode::F5;
		table[SDL_SCANCODE_F6] = Keycode::F6;
		table[SDL_SCANCODE_F7] = Keycode::F7;
		table[SDL_SCANCODE_F8] = Keycode::F8;
		table[SDL_SCANCODE_F9] = Keycode::F9;
		table[SDL_SCANCODE_F10] = Keycode::F10;
		table[SDL_SCANCODE_F11] = Keycode::F11;
		table[SDL_SCANCODE_F12] = Keycode::F12;
		table[SDL_SCANCODE_KP_0] = Keycode::KP0;
		table[SDL_SCANCODE_KP_1] = Keycode::KP1;
		table[SDL_SCANCODE_KP_2] = Keycode::KP2;
		table[SDL_SCANCODE_KP_3] = Keycode::KP3;
		table[SDL_SCANCODE_KP_4] = Keycode::KP4;
		table[SDL_SCANCODE_KP_5] = Keycode::KP5;
		table[SDL_SCANCODE_KP_6] = Keycode::KP6;
		table[SDL_SCANCODE_KP_7] = Keycode::KP7;
		table[SDL_SCANCODE_KP_8] = Keycode::KP8;
		table[SDL_SCANCODE_KP_9] = Keycode::KP9;
		table[SDL_SCANCODE_LSHIFT] = Keycode::LEFT_SHIFT;
		table[SDL_SCANCODE_LCTRL] = Keycode::LEFT_CONTROL;
		table[SDL_SCANCODE_LALT] = Keycode::LEFT_ALT;
		table[SDL_SCANCODE_LGUI] = Keycode::LEFT_SUPER;
		table[SDL_SCANCODE_RSHIFT] = Keycode::RIGHT_SHIFT;
		table[SDL_SCANCODE_RCTRL] = Keycode::RIGHT_CONTROL;
		table[SDL_SCANCODE_RALT] = Keycode::RIGHT_ALT;
		table[SDL_SCANCODE_RGUI] = Keycode::RIGHT_SUPER;
		table[SDL_SCANCODE_MENU] = Keycode::MENU;

		return table;
	}();

	if (sdl_key < 0 || sdl_key >= SDL_NUM_SCANCODES) {
		return Keycode::NONE;
	}

	return LOOKUP_TABLE[sdl_key];
}

MouseButton SDLContext::sdl_to_mousebutton(Uint8 sdl_button) {
	static const std::array<MouseButton, 5> MOUSE_BUTTON_LOOKUP_TABLE = [] {
		std::array<MouseButton, 5> table{};
		table.fill(MouseButton::NONE);

		table[SDL_BUTTON_LEFT] = MouseButton::LEFT_MOUSE;
		table[SDL_BUTTON_RIGHT] = MouseButton::RIGHT_MOUSE;
		table[SDL_BUTTON_MIDDLE] = MouseButton::MIDDLE_MOUSE;
		table[SDL_BUTTON_X1] = MouseButton::X1_MOUSE;
		table[SDL_BUTTON_X2] = MouseButton::X2_MOUSE;

		return table;
	}();

	if (sdl_button >= MOUSE_BUTTON_LOOKUP_TABLE.size()) {
		// Return NONE for invalid or unmapped button
		return MouseButton::NONE;
	}

	return MOUSE_BUTTON_LOOKUP_TABLE[sdl_button];
}

void SDLContext::clear_screen() { SDL_RenderClear(this->game_renderer.get()); }
void SDLContext::present_screen() { SDL_RenderPresent(this->game_renderer.get()); }

SDL_Rect SDLContext::get_src_rect(const Sprite & sprite) const {
	return SDL_Rect{
		.x = sprite.mask.x,
		.y = sprite.mask.y,
		.w = sprite.mask.w,
		.h = sprite.mask.h,
	};
}
SDL_Rect SDLContext::get_dst_rect(const Sprite & sprite, const vec2 & pos, const Camera & cam,
								  const vec2 & cam_pos, const double & img_scale) const {

	int width = sprite.height * sprite.aspect_ratio;
	int height = sprite.height;

	width *= img_scale * cam.zoom;
	height *= img_scale * cam.zoom;

	return SDL_Rect{
		.x = static_cast<int>((pos.x - cam_pos.x + (cam.viewport_size.x / 2) - width / 2)),
		.y = static_cast<int>((pos.y - cam_pos.y + (cam.viewport_size.y / 2) - height / 2)),
		.w = width,
		.h = height,
	};
}

void SDLContext::draw(const RenderContext & ctx) {

	SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * ctx.sprite.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * ctx.sprite.flip.flip_y));

	SDL_Rect srcrect = this->get_src_rect(ctx.sprite);
	SDL_Rect dstrect
		= this->get_dst_rect(ctx.sprite, ctx.pos, ctx.cam, ctx.cam_pos, ctx.scale);

	this->set_color_texture(ctx.sprite.sprite_image, ctx.sprite.color);
	SDL_RenderCopyEx(this->game_renderer.get(), ctx.sprite.sprite_image.texture.get(),
					 &srcrect, &dstrect, ctx.angle, NULL, render_flip);
}

void SDLContext::set_camera(const Camera & cam) {

	// resize window
	int w, h;
	SDL_GetWindowSize(this->game_window.get(), &w, &h);
	if (w != cam.screen.x || h != cam.screen.y) {
		SDL_SetWindowSize(this->game_window.get(), cam.screen.x, cam.screen.y);
	}

	double screen_aspect = cam.screen.x / cam.screen.y;
	double viewport_aspect = cam.viewport_size.x / cam.viewport_size.y;

	SDL_Rect view;
	// calculate black bars
	if (screen_aspect > viewport_aspect) {
		// letterboxing
		view.h = cam.screen.y / cam.zoom;
		view.w = cam.screen.y * viewport_aspect;
		view.x = (cam.screen.x - view.w) / 2;
		view.y = 0;
	} else {
		// pillarboxing
		view.h = cam.screen.x / viewport_aspect;
		view.w = cam.screen.x / cam.zoom;
		view.x = 0;
		view.y = (cam.screen.y - view.h) / 2;
	}
	// set drawing area
	SDL_RenderSetViewport(this->game_renderer.get(), &view);

	SDL_RenderSetLogicalSize(this->game_renderer.get(), static_cast<int>(cam.viewport_size.x),
							 static_cast<int>(cam.viewport_size.y));

	// set bg color
	SDL_SetRenderDrawColor(this->game_renderer.get(), cam.bg_color.r, cam.bg_color.g,
						   cam.bg_color.b, cam.bg_color.a);

	SDL_Rect bg = {
		.x = 0,
		.y = 0,
		.w = static_cast<int>(cam.viewport_size.x),
		.h = static_cast<int>(cam.viewport_size.y),
	};
	// fill bg color
	SDL_RenderFillRect(this->game_renderer.get(), &bg);
}

uint64_t SDLContext::get_ticks() const { return SDL_GetTicks64(); }

std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>
SDLContext::texture_from_path(const std::string & path) {

	SDL_Surface * tmp = IMG_Load(path.c_str());
	if (tmp == nullptr)
		throw runtime_error(format("SDLContext: IMG_Load error: {}", SDL_GetError()));

	std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> img_surface;
	img_surface = {tmp, [](SDL_Surface * surface) { SDL_FreeSurface(surface); }};

	SDL_Texture * tmp_texture
		= SDL_CreateTextureFromSurface(this->game_renderer.get(), img_surface.get());

	if (tmp_texture == nullptr) {
		throw runtime_error(format("SDLContext: Texture cannot be load from {}", path));
	}

	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> img_texture;
	img_texture = {tmp_texture, [](SDL_Texture * texture) { SDL_DestroyTexture(texture); }};

	SDL_SetTextureBlendMode(img_texture.get(), SDL_BLENDMODE_BLEND);
	return img_texture;
}

ivec2 SDLContext::get_size(const Texture & ctx) {
	ivec2 size;
	SDL_QueryTexture(ctx.texture.get(), NULL, NULL, &size.x, &size.y);
	return size;
}

void SDLContext::delay(int ms) const { SDL_Delay(ms); }
