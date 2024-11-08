#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstddef>
#include <iostream>

#include "../api/Sprite.h"
#include "../api/Texture.h"
#include "../api/Transform.h"
#include "../util/log.h"

#include "SDLContext.h"

using namespace crepe;

SDLContext & SDLContext::get_instance() {
	static SDLContext instance;
	return instance;
}

SDLContext::SDLContext() {
	dbg_trace();
	// FIXME: read window defaults from config manager

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		// FIXME: throw exception
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
				  << std::endl;
		return;
	}

	this->game_window = SDL_CreateWindow(
		"Crepe Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		this->viewport.w, this->viewport.h, 0);
	if (!this->game_window) {
		// FIXME: throw exception
		std::cerr << "Window could not be created! SDL_Error: "
				  << SDL_GetError() << std::endl;
	}

	this->game_renderer
		= SDL_CreateRenderer(this->game_window, -1, SDL_RENDERER_ACCELERATED);
	if (!this->game_renderer) {
		// FIXME: throw exception
		std::cerr << "Renderer could not be created! SDL_Error: "
				  << SDL_GetError() << std::endl;
		SDL_DestroyWindow(this->game_window);
		return;
	}

	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		// FIXME: throw exception
		std::cout << "SDL_image could not initialize! SDL_image Error: "
				  << IMG_GetError() << std::endl;
	}
}

SDLContext::~SDLContext() {
	dbg_trace();

	if (this->game_renderer != nullptr)
		SDL_DestroyRenderer(this->game_renderer);

	if (this->game_window != nullptr) {
		SDL_DestroyWindow(this->game_window);
	}

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

void SDLContext::clear_screen() const { SDL_RenderClear(this->game_renderer); }
void SDLContext::present_screen() const { SDL_RenderPresent(this->game_renderer); }

void SDLContext::draw(const Sprite & sprite, const Transform & transform,
					  const Camera & cam) const {

	static SDL_RendererFlip render_flip
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

	double degrees = transform.rotation * 180 / M_PI;

	SDL_RenderCopyEx(this->game_renderer, sprite.sprite_image->texture,
					 &srcrect,

					 &dstrect, degrees, NULL, render_flip);
}

void SDLContext::camera(const Camera & cam) {
	this->viewport.w = static_cast<int>(cam.aspect_width);
	this->viewport.h = static_cast<int>(cam.aspect_height);
	this->viewport.x = static_cast<int>(cam.x) - (SCREEN_WIDTH / 2);
	this->viewport.y = static_cast<int>(cam.y) - (SCREEN_HEIGHT / 2);

	SDL_SetRenderDrawColor(this->game_renderer, cam.bg_color.r, cam.bg_color.g,
						   cam.bg_color.b, cam.bg_color.a);
}

const uint64_t SDLContext::get_ticks() const { return SDL_GetTicks64(); }

SDL_Texture * SDLContext::texture_from_path(const char * path) const {
	dbg_trace();

	SDL_Surface * tmp = IMG_Load(path);
	if (!tmp) {
		std::cerr << "Error surface " << IMG_GetError << std::endl;
	}
	SDL_Texture * created_texture
		= SDL_CreateTextureFromSurface(this->game_renderer, tmp);

	if (!created_texture) {
		std::cerr << "Error could not create texture " << IMG_GetError
				  << std::endl;
	}
	SDL_FreeSurface(tmp);

	return created_texture;
}
int SDLContext::get_width(const Texture & ctx) const {
	int w;
	SDL_QueryTexture(ctx.texture, NULL, NULL, &w, NULL);
	return w;
}
int SDLContext::get_height(const Texture & ctx) const {
	int h;
	SDL_QueryTexture(ctx.texture, NULL, NULL, NULL, &h);
	return h;
}
