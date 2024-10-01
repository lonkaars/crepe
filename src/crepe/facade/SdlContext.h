#pragma once

#include "Texture.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <string>

namespace crepe {

class SdlContext {

private:
	SdlContext();
	virtual ~SdlContext();

	// singleton
	static SdlContext & get_instance();
	SdlContext(const SdlContext &) = delete;
	SdlContext(SdlContext &&) = delete;
	SdlContext & operator=(const SdlContext &) = delete;
	SdlContext & operator=(SdlContext &&) = delete;

	SDL_Texture* setTextureFromPath(const char*);

private:
	friend class Texture;

	SDL_Window* m_game_window;
	SDL_Renderer* m_game_renderer;
};

} //

