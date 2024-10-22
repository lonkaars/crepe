#pragma once

#include "SDL_rect.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

namespace crepe {


class SdlContext {

public:

	void handleEvents(bool& running);
	void clearScreen();
	void presentScreen();
	void draw(const api::Sprite&, const api::Transform&);

	// singleton
	static SdlContext & get_instance();
	SDL_Texture* setTextureFromPath(const char*);
	SDL_Texture* setTextureFromPath(const char*, SDL_Rect& clip, const int row, const int col);

private:
	SdlContext();
	virtual ~SdlContext();

	SdlContext(const SdlContext &) = delete;
	SdlContext(SdlContext &&) = delete;
	SdlContext & operator=(const SdlContext &) = delete;
	SdlContext & operator=(SdlContext &&) = delete;


private:

	SDL_Window* m_game_window;
	SDL_Renderer* m_game_renderer;
};

} //

