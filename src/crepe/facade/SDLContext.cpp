#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
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
#include "api/Text.h"
#include "api/Transform.h"
#include "facade/Font.h"
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

	if (TTF_Init() == -1) {
		throw runtime_error(format("SDL_ttf initialization failed: {}", TTF_GetError()));
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
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

Keycode SDLContext::sdl_to_keycode(SDL_Scancode sdl_key) {
	if (!lookup_table.contains(sdl_key)) return Keycode::NONE;
	return lookup_table.at(sdl_key);
}

const keyboard_state_t & SDLContext::get_keyboard_state() {
	SDL_PumpEvents();
	const Uint8 * current_state = SDL_GetKeyboardState(nullptr);

	for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {

		Keycode key = sdl_to_keycode(static_cast<SDL_Scancode>(i));
		if (key != Keycode::NONE) {
			this->keyboard_state[key] = current_state[i] != 0;
		}
	}
	return this->keyboard_state;
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

void SDLContext::draw_text(const RenderText & data) {

	const Text & text = data.text;
	const Font & font = data.font;
	const Transform & transform = data.transform;
	std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> font_surface;
	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> font_texture;

	SDL_Color color{
		.r = text.data.text_color.r,
		.g = text.data.text_color.g,
		.b = text.data.text_color.b,
		.a = text.data.text_color.a,
	};
	SDL_Surface * tmp_font_surface
		= TTF_RenderText_Solid(font.get_font(), text.text.c_str(), color);
	if (!tmp_font_surface) {
		throw runtime_error(format("draw_text: font surface error: {}", SDL_GetError()));
	}
	font_surface = {tmp_font_surface, [](SDL_Surface * surface) { SDL_FreeSurface(surface); }};

	SDL_Texture * tmp_font_texture
		= SDL_CreateTextureFromSurface(this->game_renderer.get(), font_surface.get());
	if (!tmp_font_texture) {
		throw runtime_error(format("draw_text: font texture error: {}", SDL_GetError()));
	}
	font_texture
		= {tmp_font_texture, [](SDL_Texture * texture) { SDL_DestroyTexture(texture); }};

	vec2 size = text.dimensions * cam_aux_data.render_scale;
	vec2 screen_pos = (transform.position + text.offset - cam_aux_data.cam_pos
					   + (cam_aux_data.zoomed_viewport) / 2)
						  * cam_aux_data.render_scale
					  - size / 2 + cam_aux_data.bar_size;

	SDL_FRect dstrect{
		.x = screen_pos.x,
		.y = screen_pos.y,
		.w = size.x,
		.h = size.y,
	};

	SDL_RenderCopyExF(this->game_renderer.get(), font_texture.get(), NULL, &dstrect, 0, NULL,
					  SDL_FLIP_NONE);
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

std::vector<EventData> SDLContext::get_events() {
	std::vector<EventData> event_list;
	SDL_Event event;
	const CameraAuxiliaryData & cam = this->cam_aux_data;
	while (SDL_PollEvent(&event)) {
		ivec2 mouse_pos;
		mouse_pos.x = (event.button.x - cam.bar_size.x) / cam.render_scale.x;
		mouse_pos.y = (event.button.y - cam.bar_size.y) / cam.render_scale.y;
		switch (event.type) {
			case SDL_QUIT:
				event_list.push_back({.event_type = EventType::SHUTDOWN});
				break;
			case SDL_KEYDOWN:
				event_list.push_back(EventData{
					.event_type = EventType::KEY_DOWN,
					.data = {
						.key_data = {
							.key = this->sdl_to_keycode(event.key.keysym.scancode),
							.key_repeat = event.key.repeat != 0,
						},
					},
				});
				break;

			case SDL_KEYUP:
				event_list.push_back(EventData{
					.event_type = EventType::KEY_UP,
					.data = {
						.key_data = {
							.key = this->sdl_to_keycode(event.key.keysym.scancode),
							.key_repeat = event.key.repeat != 0,
						},
					},
				});
				break;

			case SDL_MOUSEBUTTONDOWN:
				event_list.push_back(EventData{
					.event_type = EventType::MOUSE_DOWN,
					.data = {
						.mouse_data = {
							.mouse_button = this->sdl_to_mousebutton(event.button.button),
							.mouse_position = mouse_pos,
						},
					},
				});
				break;
			case SDL_MOUSEBUTTONUP:
				event_list.push_back(EventData{
					.event_type = EventType::MOUSE_UP,
					.data = {
						.mouse_data = {
							.mouse_button = this->sdl_to_mousebutton(event.button.button),
							.mouse_position = mouse_pos,
						},
					},
				});
				break;

			case SDL_MOUSEMOTION:
				event_list.push_back(EventData{
					.event_type = EventType::MOUSE_MOVE,
					.data = {
						.mouse_data = {
							.mouse_position = mouse_pos,
							.rel_mouse_move = {event.motion.xrel, event.motion.yrel},
						},
					},
				});
				break;

			case SDL_MOUSEWHEEL:
				event_list.push_back(EventData{
					.event_type = EventType::MOUSE_WHEEL,
					.data = {
						.mouse_data = {
							.mouse_position = mouse_pos,
							.scroll_direction = event.wheel.y < 0 ? -1 : 1,
							.scroll_delta = event.wheel.preciseY,
						},
					},
				});
				break;
			case SDL_WINDOWEVENT:
				this->handle_window_event(event.window, event_list);
				break;
		}
	}

	return event_list;
}

void SDLContext::handle_window_event(const SDL_WindowEvent & window_event,
									 std::vector<EventData> & event_list) {
	switch (window_event.event) {
		case SDL_WINDOWEVENT_EXPOSED:
			event_list.push_back(EventData{EventType::WINDOW_EXPOSE});
			break;
		case SDL_WINDOWEVENT_RESIZED:
			event_list.push_back(EventData{
					.event_type = EventType::WINDOW_RESIZE,
					.data = {
						.window_data = {
							.resize_dimension = {window_event.data1, window_event.data2}
						},
					},
				});
			break;
		case SDL_WINDOWEVENT_MOVED:
			event_list.push_back(EventData{
					.event_type = EventType::WINDOW_MOVE,
					.data = {
						.window_data = {
							.move_delta = {window_event.data1, window_event.data2}
						},
					},
				});
			break;

		case SDL_WINDOWEVENT_MINIMIZED:
			event_list.push_back(EventData{EventType::WINDOW_MINIMIZE});
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			event_list.push_back(EventData{EventType::WINDOW_MAXIMIZE});
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			event_list.push_back(EventData{EventType::WINDOW_FOCUS_GAIN});
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			event_list.push_back(EventData{EventType::WINDOW_FOCUS_LOST});
			break;
	}
}

void SDLContext::set_color_texture(const Texture & texture, const Color & color) {
	SDL_SetTextureColorMod(texture.get_img(), color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture.get_img(), color.a);
}

Asset SDLContext::get_font_from_name(const std::string & font_family) {
	return this->font_facade.get_font_asset(font_family);
}
