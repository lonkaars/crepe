#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "api/Sprite.h"
#include "api/Transform.h"

#include "RenderSystem.h"

namespace crepe::api {
class Texture;
}

namespace crepe {

class SdlContext {

public:
	// singleton
	static SdlContext & get_instance();
	SdlContext(const SdlContext &) = delete;
	SdlContext(SdlContext &&) = delete;
	SdlContext & operator=(const SdlContext &) = delete;
	SdlContext & operator=(SdlContext &&) = delete;

	//TODO decide events wouter?

private:
	void handle_events(bool & running);

private:
	SdlContext();
	virtual ~SdlContext();

private:
	friend class api::Texture;
	SDL_Texture * texture_from_path(const char *);
	//SDL_Texture* setTextureFromPath(const char*, SDL_Rect& clip, const int row, const int col);

private:
	friend class RenderSystem;
	void draw(const api::Sprite &, const api::Transform &);
	void clear_screen();
	void present_screen();

private:
	SDL_Window * game_window = nullptr;
	SDL_Renderer * game_renderer = nullptr;
};

} // namespace crepe
