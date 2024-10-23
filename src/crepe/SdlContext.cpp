

#include "SdlContext.h"

#include "api/Sprite.h"
#include "api/Texture.h"
#include "api/Transform.h"
#include "util/log.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstddef>
#include <iostream>

using namespace crepe;

SdlContext & SdlContext::get_instance() {
	static SdlContext instance;
	return instance;
}

void SdlContext::handle_events(bool & running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}

SdlContext::~SdlContext() {
	dbg_trace();

	if (m_game_renderer != nullptr) SDL_DestroyRenderer(m_game_renderer);

	if (m_game_window != nullptr) {
		SDL_DestroyWindow(m_game_window);
	}

	IMG_Quit();
	SDL_Quit();
}

void SdlContext::clear_screen() { SDL_RenderClear(this->m_game_renderer); }

SdlContext::SdlContext() {
	dbg_trace();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
				  << std::endl;
		return;
	}

	m_game_window = SDL_CreateWindow(
		"Crepe Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1920, 1080, SDL_WINDOW_SHOWN);
	if (!m_game_window) {
		std::cerr << "Window could not be created! SDL_Error: "
				  << SDL_GetError() << std::endl;
	}

	m_game_renderer
		= SDL_CreateRenderer(m_game_window, -1, SDL_RENDERER_ACCELERATED);
	if (!m_game_renderer) {
		std::cerr << "Renderer could not be created! SDL_Error: "
				  << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_game_window);
		return;
	}

	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		std::cout << "SDL_image could not initialize! SDL_image Error: "
				  << IMG_GetError() << std::endl;
	}
}
void SdlContext::present_screen() { SDL_RenderPresent(this->m_game_renderer); }

void SdlContext::draw(const api::Sprite & sprite,
					  const api::Transform & transform) {

	static SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * sprite.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * sprite.flip.flip_y));

	int w, h;
	SDL_QueryTexture(sprite.sprite_image->m_texture, NULL, NULL, &w, &h);
	// needs maybe camera for position
	SDL_Rect dstrect = {
		.x = static_cast<int>(transform.position.x),
		.y = static_cast<int>(transform.position.y),
		.w = static_cast<int>(w * transform.scale),
		.h = static_cast<int>(h * transform.scale),
	};
	
	double degrees = transform.rotation * 180 / M_PI;
	SDL_RenderCopyEx(this->m_game_renderer, sprite.sprite_image->m_texture,
					 NULL, &dstrect, degrees, NULL, render_flip);
}

/*
SDL_Texture * SdlContext::setTextureFromPath(const char * path, SDL_Rect & clip,
											 const int row, const int col) {
	dbg_trace();

	SDL_Surface * tmp = IMG_Load(path);
	if (!tmp) {
		std::cerr << "Error surface " << IMG_GetError << std::endl;
	}

	clip.
		w = tmp->w / col;
	clip.h = tmp->h / row;

	SDL_Texture * CreatedTexture
		= SDL_CreateTextureFromSurface(m_game_renderer, tmp);

	if (!CreatedTexture) {
		std::cerr << "Error could not create texture " << IMG_GetError
				  << std::endl;
	}
	SDL_FreeSurface(tmp);

	return CreatedTexture;
}
*/

SDL_Texture * SdlContext::texture_from_path(const char * path) {
	dbg_trace();
	
	SDL_Surface * tmp = IMG_Load(path);
	if (!tmp) {
		std::cerr << "Error surface " << IMG_GetError << std::endl;
	}
	SDL_Texture * created_texture
		= SDL_CreateTextureFromSurface(m_game_renderer, tmp);

	if (!created_texture) {
		std::cerr << "Error could not create texture " << IMG_GetError
				  << std::endl;
	}
	SDL_FreeSurface(tmp);

	return created_texture;
}
