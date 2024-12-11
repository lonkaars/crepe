#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <stdexcept>

#include "../api/Camera.h"
#include "../api/Color.h"
#include "../api/Config.h"
#include "../api/Sprite.h"
#include "../util/Log.h"
#include "manager/Mediator.h"

#include "SDLContext.h"
#include "Texture.h"
#include "types.h"

using namespace crepe;
using namespace std;

SDLContext::SDLContext(Mediator & mediator) {
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

	mediator.sdl_context = *this;
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
void SDLContext::present_screen() {
	SDL_SetRenderDrawColor(this->game_renderer.get(), 0, 0, 0, 255);
	SDL_RenderFillRectF(this->game_renderer.get(), &black_bars[0]);
	SDL_RenderFillRectF(this->game_renderer.get(), &black_bars[1]);
	SDL_RenderPresent(this->game_renderer.get());
}

SDL_FRect SDLContext::get_dst_rect(const DestinationRectangleData & ctx) const {

	const Sprite::Data & data = ctx.sprite.data;

	float aspect_ratio
		= (ctx.sprite.aspect_ratio == 0) ? ctx.texture.get_ratio() : ctx.sprite.aspect_ratio;

	vec2 size = data.size;
	if (data.size.x == 0 && data.size.y != 0) {
		size.x = data.size.y * aspect_ratio;
	}
	if (data.size.y == 0 && data.size.x != 0) {
		size.y = data.size.x / aspect_ratio;
	}
	size *= cam_aux_data.render_scale * ctx.img_scale * data.scale_offset;

	vec2 screen_pos = (ctx.pos + data.position_offset - cam_aux_data.cam_pos
					   + (cam_aux_data.zoomed_viewport) / 2)
						  * cam_aux_data.render_scale
					  - size / 2 + cam_aux_data.bar_size;

	return SDL_FRect{
		.x = screen_pos.x,
		.y = screen_pos.y,
		.w = size.x,
		.h = size.y,
	};
}

void SDLContext::draw(const RenderContext & ctx) {
	const Sprite::Data & data = ctx.sprite.data;
	SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * data.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * data.flip.flip_y));

	SDL_Rect srcrect;
	SDL_Rect * srcrect_ptr = NULL;
	if (ctx.sprite.mask.w != 0 || ctx.sprite.mask.h != 0) {
		srcrect.w = ctx.sprite.mask.w;
		srcrect.h = ctx.sprite.mask.h;
		srcrect.x = ctx.sprite.mask.x;
		srcrect.y = ctx.sprite.mask.y;
		srcrect_ptr = &srcrect;
	}

	SDL_FRect dstrect = this->get_dst_rect(SDLContext::DestinationRectangleData{
		.sprite = ctx.sprite,
		.texture = ctx.texture,
		.pos = ctx.pos,
		.img_scale = ctx.scale,
	});

	double angle = ctx.angle + data.angle_offset;

	this->set_color_texture(ctx.texture, ctx.sprite.data.color);
	SDL_RenderCopyExF(this->game_renderer.get(), ctx.texture.get_img(), srcrect_ptr, &dstrect,
					  angle, NULL, render_flip);
}

void SDLContext::update_camera_view(const Camera & cam, const vec2 & new_pos) {

	const Camera::Data & cam_data = cam.data;
	// resize window
	int w, h;
	SDL_GetWindowSize(this->game_window.get(), &w, &h);
	if (w != cam.screen.x || h != cam.screen.y) {
		SDL_SetWindowSize(this->game_window.get(), cam.screen.x, cam.screen.y);
	}

	vec2 & zoomed_viewport = this->cam_aux_data.zoomed_viewport;
	vec2 & bar_size = this->cam_aux_data.bar_size;
	vec2 & render_scale = this->cam_aux_data.render_scale;
	this->cam_aux_data.cam_pos = new_pos;

	zoomed_viewport = cam.viewport_size * cam_data.zoom;
	float screen_aspect = static_cast<float>(cam.screen.x) / cam.screen.y;
	float viewport_aspect = zoomed_viewport.x / zoomed_viewport.y;

	// calculate black bars
	if (screen_aspect > viewport_aspect) {
		// pillarboxing
		float scale = cam.screen.y / zoomed_viewport.y;
		float adj_width = zoomed_viewport.x * scale;
		float bar_width = (cam.screen.x - adj_width) / 2;
		this->black_bars[0] = {0, 0, bar_width, (float) cam.screen.y};
		this->black_bars[1] = {(cam.screen.x - bar_width), 0, bar_width, (float) cam.screen.y};

		bar_size = {bar_width, 0};
		render_scale.x = render_scale.y = scale;
	} else {
		// letterboxing
		float scale = cam.screen.x / (cam.viewport_size.x * cam_data.zoom);
		float adj_height = cam.viewport_size.y * scale;
		float bar_height = (cam.screen.y - adj_height) / 2;
		this->black_bars[0] = {0, 0, (float) cam.screen.x, bar_height};
		this->black_bars[1]
			= {0, (cam.screen.y - bar_height), (float) cam.screen.x, bar_height};

		bar_size = {0, bar_height};
		render_scale.x = render_scale.y = scale;
	}

	SDL_SetRenderDrawColor(this->game_renderer.get(), cam_data.bg_color.r, cam_data.bg_color.g,
						   cam_data.bg_color.b, cam_data.bg_color.a);

	SDL_Rect bg = {
		.x = 0,
		.y = 0,
		.w = cam.screen.x,
		.h = cam.screen.y,
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
	SDL_QueryTexture(ctx.get_img(), NULL, NULL, &size.x, &size.y);
	return size;
}

void SDLContext::delay(int ms) const { SDL_Delay(ms); }

std::vector<SDLContext::EventData> SDLContext::get_events() {
	std::vector<SDLContext::EventData> event_list;
	SDL_Event event;
	const CameraAuxiliaryData & cam = this->cam_aux_data;
	while (SDL_PollEvent(&event)) {
		ivec2 mouse_pos;
		mouse_pos.x = (event.button.x - cam.bar_size.x) / cam.render_scale.x;
		mouse_pos.y = (event.button.y - cam.bar_size.y) / cam.render_scale.y;
		switch (event.type) {
			case SDL_QUIT:
				event_list.push_back(EventData{
					.event_type = SDLContext::EventType::SHUTDOWN,
				});
				break;
			case SDL_KEYDOWN:
				event_list.push_back(EventData{
					.event_type = SDLContext::EventType::KEYDOWN,
					.key = sdl_to_keycode(event.key.keysym.scancode),
					.key_repeat = (event.key.repeat != 0),
				});
				break;
			case SDL_KEYUP:
				event_list.push_back(EventData{
					.event_type = SDLContext::EventType::KEYUP,
					.key = sdl_to_keycode(event.key.keysym.scancode),
				});
				break;
			case SDL_MOUSEBUTTONDOWN:
				event_list.push_back(EventData{
					.event_type = SDLContext::EventType::MOUSEDOWN,
					.mouse_button = sdl_to_mousebutton(event.button.button),
					.mouse_position = mouse_pos,
				});
				break;
			case SDL_MOUSEBUTTONUP: {
				int x, y;
				SDL_GetMouseState(&x, &y);
				event_list.push_back(EventData{
					.event_type = SDLContext::EventType::MOUSEUP,
					.mouse_button = sdl_to_mousebutton(event.button.button),
					.mouse_position = mouse_pos,
				});
			} break;

			case SDL_MOUSEMOTION: {
				event_list.push_back(
					EventData{.event_type = SDLContext::EventType::MOUSEMOVE,
							  .mouse_position = mouse_pos,
							  .rel_mouse_move = {event.motion.xrel, event.motion.yrel}});
			} break;

			case SDL_MOUSEWHEEL: {
				event_list.push_back(EventData{
					.event_type = SDLContext::EventType::MOUSEWHEEL,
					.mouse_position = mouse_pos,
					// TODO: why is this needed?
					.scroll_direction = event.wheel.y < 0 ? -1 : 1,
					.scroll_delta = event.wheel.preciseY,
				});
			} break;
		}
	}
	return event_list;
}
void SDLContext::set_color_texture(const Texture & texture, const Color & color) {
	SDL_SetTextureColorMod(texture.get_img(), color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture.get_img(), color.a);
}
