#pragma once

#include "SDL_rect.h"
#include "Texture.h"
#include "api/spritesheet.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

namespace crepe {

class Texture;
class Spritesheet;

class SdlContext {

public:
	void loop(const Texture& , api::Spritesheet&);

	// singleton
	static SdlContext & get_instance();
private:
	SdlContext();
	virtual ~SdlContext();

	SdlContext(const SdlContext &) = delete;
	SdlContext(SdlContext &&) = delete;
	SdlContext & operator=(const SdlContext &) = delete;
	SdlContext & operator=(SdlContext &&) = delete;

	SDL_Texture* setTextureFromPath(const char*);
	SDL_Texture* setTextureFromPath(const char*, SDL_Rect& clip, const int row, const int col);

private:
	friend class Texture;
	friend class api::Spritesheet;

	SDL_Window* m_game_window;
	SDL_Renderer* m_game_renderer;
};

} //

