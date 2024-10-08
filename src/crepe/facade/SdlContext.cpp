

#include "SdlContext.h"
#include "SDL_rect.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include "facade/Texture.h"
#include "util/log.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <iostream>
#include <ostream>

using namespace crepe;

SdlContext & SdlContext::get_instance() {
	static SdlContext instance;
	return instance;
}

void SdlContext::handleEvents(bool & running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}
}
void SdlContext::clearScreen() { SDL_RenderClear(this->m_game_renderer); }

void SdlContext::presentScreen() { SDL_RenderPresent(this->m_game_renderer); }

void SdlContext::draw(const api::Sprite & sprite, const api::Transform& transform) {
	static SDL_RendererFlip renderFlip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * sprite.flip.flipX)
							  | (SDL_FLIP_VERTICAL * sprite.flip.flipY));

	// needs maybe camera for position
	static SDL_Rect dstrect = {
		.x = static_cast<int>(transform.position.x),
		.y = static_cast<int>(transform.position.y),
		.w = static_cast<int>(sprite.sprite_image->get_rect().w * transform.scale),
		.h = static_cast<int>(sprite.sprite_image->get_rect().h * transform.scale),
	};

	SDL_RenderCopyEx(this->m_game_renderer, sprite.sprite_image->get_texture(),
					 &sprite.sprite_image->get_rect(), &dstrect, 0, NULL, renderFlip);
}

SdlContext::SdlContext() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
				  << std::endl;
		return;
	}

	m_game_window
		= SDL_CreateWindow("Crepe Game Engine", SDL_WINDOWPOS_CENTERED,
						   SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
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
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image could not initialize! SDL_image Error: "
				  << IMG_GetError() << std::endl;
	}
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
}

SdlContext::~SdlContext() {
	if (m_game_renderer) SDL_DestroyRenderer(m_game_renderer);

	if (m_game_window) {
		SDL_DestroyWindow(m_game_window);
	}
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture * SdlContext::setTextureFromPath(const char * path, SDL_Rect & clip,
											 const int row, const int col) {
	dbg_trace();

	SDL_Surface * tmp = IMG_Load(path);
	if (!tmp) {
		std::cerr << "Error surface " << IMG_GetError << std::endl;
	}

	clip.w = tmp->w / col;
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

SDL_Texture * SdlContext::setTextureFromPath(const char * path) {
	dbg_trace();

	SDL_Surface * tmp = IMG_Load(path);
	if (!tmp) {
		std::cerr << "Error surface " << IMG_GetError << std::endl;
	}
	SDL_Texture * CreatedTexture
		= SDL_CreateTextureFromSurface(m_game_renderer, tmp);

	if (!CreatedTexture) {
		std::cerr << "Error could not create texture " << IMG_GetError
				  << std::endl;
	}
	SDL_FreeSurface(tmp);

	return CreatedTexture;
}

