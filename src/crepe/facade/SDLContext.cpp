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

#include "../api/Sprite.h"
#include "../api/Texture.h"
#include "../api/Transform.h"
#include "../util/Log.h"
#include "api/Vector2.h"

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
						   this->viewport.w, this->viewport.h, SDL_WINDOW_RESIZABLE);
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

void SDLContext::handle_events(bool & running) {
	//TODO: wouter i need events
	/*
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			triggerEvent(KeyPressedEvent(getCustomKey(event.key.keysym.sym)));
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			triggerEvent(MousePressedEvent(x, y));
			break;
	}
	*/
}

void SDLContext::clear_screen() { SDL_RenderClear(this->game_renderer.get()); }
void SDLContext::present_screen() { SDL_RenderPresent(this->game_renderer.get()); }


void SDLContext::draw(const Sprite & sprite, const Transform & transform, const Camera & cam) {

	SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * sprite.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * sprite.flip.flip_y));
	
	double screen_aspect = cam.screen.x / cam.screen.y;
	double viewport_aspect = cam.viewport.x / cam.viewport.y;
	Vector2 scale;

	if (screen_aspect > viewport_aspect) {
		scale.x = scale.y = cam.screen.x / cam.viewport.x;
	} else {
		scale.y = scale.x = cam.screen.y / cam.viewport.y;
	}

	Vector2 zoomed_viewport = cam.viewport * cam.zoom;
	Vector2 pixel_coord = (transform.position - cam.pos) * scale;

	double pixel_w = sprite.sprite_rect.w * transform.scale * scale.x;
	double pixel_h = sprite.sprite_rect.h * transform.scale * scale.y;

	// decides which part of the sprite will be drawn
	SDL_Rect srcrect = {
		.x = sprite.sprite_rect.x,
		.y = sprite.sprite_rect.y,
		.w = sprite.sprite_rect.w,
		.h = sprite.sprite_rect.h,
	};

	// decides where the clipped image is drawn
	SDL_Rect dstrect = {
		.x = static_cast<int>(pixel_coord.x),
		.y = static_cast<int>(pixel_coord.y),
		.w = static_cast<int>(pixel_w),
		.h = static_cast<int>(pixel_h),
	};

	SDL_RenderCopyEx(this->game_renderer.get(), sprite.sprite_image->texture.get(), &srcrect,
					 &dstrect, transform.rotation, NULL, render_flip);
}

void SDLContext::camera(const Camera & cam) {

	if (this->viewport.w != cam.screen.x && this->viewport.h != cam.screen.y) {
		this->viewport.w = cam.screen.x;
		this->viewport.h = cam.screen.y;
		SDL_SetWindowSize(this->game_window.get(), cam.screen.x	, cam.screen.y);
	}

	/*
	this->viewport.x = static_cast<int>(cam.x) - (SCREEN_WIDTH / 2);
	this->viewport.y = static_cast<int>(cam.y) - (SCREEN_HEIGHT / 2);

	*/

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
