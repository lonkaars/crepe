#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <array>

#include "../api/Sprite.h"
#include "../api/Texture.h"
#include "../api/Transform.h"
#include "../api/EventManager.h"
#include "../util/Log.h"


#include "SDLContext.h"

using namespace crepe;
using namespace std;

SDLContext & SDLContext::get_instance() {
	static SDLContext instance;
	return instance;
}

SDLContext::SDLContext() {
	dbg_trace();
	// FIXME: read window defaults from config manager

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// FIXME: throw exception
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_Window * tmp_window
		= SDL_CreateWindow("Crepe Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						   this->viewport.w, this->viewport.h, 0);
	if (!tmp_window) {
		// FIXME: throw exception
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return;
	}
	this->game_window = {tmp_window, [](SDL_Window * window) { SDL_DestroyWindow(window); }};

	SDL_Renderer * tmp_renderer
		= SDL_CreateRenderer(this->game_window.get(), -1, SDL_RENDERER_ACCELERATED);
	if (!tmp_renderer) {
		// FIXME: throw exception
		std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
				  << std::endl;
		SDL_DestroyWindow(this->game_window.get());
		return;
	}

	this->game_renderer
		= {tmp_renderer, [](SDL_Renderer * renderer) { SDL_DestroyRenderer(renderer); }};

	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		// FIXME: throw exception
		std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError()
				  << std::endl;
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

void SDLContext::handle_events(bool &running) {
    EventManager& event_manager = EventManager::get_instance();
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                event_manager.trigger_event(ShutDownEvent{});
                break;

            case SDL_KEYDOWN:
                std::cout << "keyDown: " << event.key.keysym.sym << std::endl;
                event_manager.trigger_event<KeyPressEvent>(KeyPressEvent{
                    .repeat = event.key.repeat,
                    .key = this->sdl_to_keycode(event.key.keysym.scancode)
                });
                break;

            case SDL_KEYUP:
                event_manager.trigger_event<KeyReleaseEvent>(KeyReleaseEvent{
                    .key = this->sdl_to_keycode(event.key.keysym.scancode),
                });
                break;

            case SDL_MOUSEBUTTONDOWN:
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    event_manager.trigger_event<MousePressEvent>(MousePressEvent{
                        .mouse_x = x,
                        .mouse_y = y,
                        .button = this->sdl_to_mousebutton(event.button.button)
                    });
                }
                break;

            case SDL_MOUSEBUTTONUP:
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    event_manager.trigger_event<MouseReleaseEvent>(MouseReleaseEvent{
                        .mouse_x = x,
                        .mouse_y = y,
                        .button = this->sdl_to_mousebutton(event.button.button)
                    });
                }
                break;

            case SDL_MOUSEMOTION:
                event_manager.trigger_event<MouseMoveEvent>(MouseMoveEvent{
                    .mouse_x = event.motion.x,
                    .mouse_y = event.motion.y,
                    .rel_x = event.motion.xrel,
                    .rel_y = event.motion.yrel
                });
                break;

            case SDL_MOUSEWHEEL:
                event_manager.trigger_event<MouseScrollEvent>(MouseScrollEvent{
                    .scroll_x = event.wheel.x,
                    .scroll_y = event.wheel.y,
                    .direction = (event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED ? -1 : 1)
                });
                break;

        }
    }
}



Keycode SDLContext::sdl_to_keycode(SDL_Keycode sdl_key) {
    static const std::array<Keycode, SDL_NUM_SCANCODES> LOOKUP_TABLE = [] {
        std::array<Keycode, SDL_NUM_SCANCODES> table{};
		 // Default to NONE for unmapped keys
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
    static const std::array<MouseButton, 8> MOUSE_BUTTON_LOOKUP_TABLE = [] {
        std::array<MouseButton, 8> table{};
        table.fill(MouseButton::NONE); // Default to NONE for unmapped buttons

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

    return MOUSE_BUTTON_LOOKUP_TABLE[sdl_button];  // Return mapped button
}
void SDLContext::clear_screen() { SDL_RenderClear(this->game_renderer.get()); }
void SDLContext::present_screen() { SDL_RenderPresent(this->game_renderer.get()); }

void SDLContext::draw(const Sprite & sprite, const Transform & transform, const Camera & cam) {

	SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * sprite.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * sprite.flip.flip_y));

	double adjusted_x = (transform.position.x - cam.x) * cam.zoom;
	double adjusted_y = (transform.position.y - cam.y) * cam.zoom;
	double adjusted_w = sprite.sprite_rect.w * transform.scale * cam.zoom;
	double adjusted_h = sprite.sprite_rect.h * transform.scale * cam.zoom;

	SDL_Rect srcrect = {
		.x = sprite.sprite_rect.x,
		.y = sprite.sprite_rect.y,
		.w = sprite.sprite_rect.w,
		.h = sprite.sprite_rect.h,
	};

	SDL_Rect dstrect = {
		.x = static_cast<int>(adjusted_x),
		.y = static_cast<int>(adjusted_y),
		.w = static_cast<int>(adjusted_w),
		.h = static_cast<int>(adjusted_h),
	};

	SDL_RenderCopyEx(this->game_renderer.get(), sprite.sprite_image->texture.get(), &srcrect,
					 &dstrect, transform.rotation, NULL, render_flip);
}

void SDLContext::camera(const Camera & cam) {
	this->viewport.w = static_cast<int>(cam.aspect_width);
	this->viewport.h = static_cast<int>(cam.aspect_height);
	this->viewport.x = static_cast<int>(cam.x) - (SCREEN_WIDTH / 2);
	this->viewport.y = static_cast<int>(cam.y) - (SCREEN_HEIGHT / 2);

	SDL_SetRenderDrawColor(this->game_renderer.get(), cam.bg_color.r, cam.bg_color.g,
						   cam.bg_color.b, cam.bg_color.a);
}

uint64_t SDLContext::get_ticks() const { return SDL_GetTicks64(); }

std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>
SDLContext::texture_from_path(const std::string & path) {

	SDL_Surface * tmp = IMG_Load(path.c_str());
	if (tmp == nullptr) {
		tmp = IMG_Load("../asset/texture/ERROR.png");
	}

	std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> img_surface;
	img_surface = {tmp, [](SDL_Surface * surface) { SDL_FreeSurface(surface); }};

	SDL_Texture * tmp_texture
		= SDL_CreateTextureFromSurface(this->game_renderer.get(), img_surface.get());

	if (tmp_texture == nullptr) {
		throw runtime_error(format("Texture cannot be load from {}", path));
	}

	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> img_texture;
	img_texture = {tmp_texture, [](SDL_Texture * texture) { SDL_DestroyTexture(texture); }};

	return img_texture;
}
int SDLContext::get_width(const Texture & ctx) const {
	int w;
	SDL_QueryTexture(ctx.texture.get(), NULL, NULL, &w, NULL);
	return w;
}
int SDLContext::get_height(const Texture & ctx) const {
	int h;
	SDL_QueryTexture(ctx.texture.get(), NULL, NULL, NULL, &h);
	return h;
}
void SDLContext::delay(int ms) const { SDL_Delay(ms); }
