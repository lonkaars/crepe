#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstddef>
#include <iostream>

#include "api/Camera.h"
#include "api/Sprite.h"
#include "api/Texture.h"
#include "api/Transform.h"
#include "api/event.h"
#include "api/eventManager.h"
#include "keyCodes.h"
#include "util/log.h"

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
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			triggerEvent(
				api::KeyPressedEvent(getCustomKey(event.key.keysym.sym)));
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			triggerEvent(api::MousePressedEvent(x, y));
			break;
	}
}

void SDLContext::clear_screen() { SDL_RenderClear(this->game_renderer); }
void SDLContext::present_screen() { SDL_RenderPresent(this->game_renderer); }

void SDLContext::draw(const api::Sprite & sprite,
					  const api::Transform & transform,
					  const api::Camera & cam ) {

	static SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * sprite.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * sprite.flip.flip_y));

	int img_width, img_height;
	SDL_QueryTexture(sprite.sprite_image->texture, NULL, NULL, &img_width, &img_height);

   	double adjusted_x = (transform.position.x - cam.x) * cam.zoom;
    double adjusted_y = (transform.position.y - cam.y) * cam.zoom;
    double adjusted_w = img_width * transform.scale * cam.zoom;
    double adjusted_h = img_height * transform.scale * cam.zoom;

    SDL_Rect srcrect;
    srcrect.x = std::max(0, static_cast<int>((cam.x - transform.position.x) / transform.scale));
    srcrect.y = std::max(0, static_cast<int>((cam.y - transform.position.y) / transform.scale));
    srcrect.w = std::min(static_cast<int>(img_width), static_cast<int>(cam.aspect_width / cam.zoom));
    srcrect.h = std::min(static_cast<int>(img_height), static_cast<int>(cam.aspect_height / cam.zoom));

    SDL_Rect dstrect = {
        .x = static_cast<int>(adjusted_x),
        .y = static_cast<int>(adjusted_y),
        .w = static_cast<int>(srcrect.w * cam.zoom),
        .h = static_cast<int>(srcrect.h * cam.zoom),
    };

	double degrees = transform.rotation * 180 / M_PI;

	SDL_RenderCopyEx(this->game_renderer, sprite.sprite_image->texture, NULL,
					 &dstrect, degrees, NULL, render_flip);
}

SDL_Texture * SDLContext::texture_from_path(const char * path) {
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

void SDLContext::camera(const api::Camera & cam) {
    int new_width = static_cast<int>(cam.aspect_width * cam.zoom);
    int new_height = static_cast<int>(cam.aspect_height * cam.zoom);

    this->viewport.w = std::max(0, new_width);
    this->viewport.h = std::max(0, new_height);

    this->viewport.x = static_cast<int>(cam.x);
    this->viewport.y = static_cast<int>(cam.y);

	std::cout << this->viewport.x << " " << this->viewport.y << std::endl;

	SDL_RenderSetViewport(this->game_renderer, &this->viewport);
	SDL_SetRenderDrawColor(this->game_renderer, cam.bg_color.r, cam.bg_color.g,
						   cam.bg_color.b, cam.bg_color.a);
}
