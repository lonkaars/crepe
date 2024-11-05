#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "../system/RenderSystem.h"

namespace crepe {

class Texture;
class SDLContext {

public:
	// singleton
	static SDLContext & get_instance();
	SDLContext(const SDLContext &) = delete;
	SDLContext(SDLContext &&) = delete;
	SDLContext & operator=(const SDLContext &) = delete;
	SDLContext & operator=(SDLContext &&) = delete;

	//TODO decide events wouter?

private:
	void handle_events(bool & running);

private:
	SDLContext();
	virtual ~SDLContext();

private:
	friend class Texture;
	SDL_Texture * texture_from_path(const char *);
	//SDL_Texture* setTextureFromPath(const char*, SDL_Rect& clip, const int row, const int col);

private:
	friend class RenderSystem;
	void draw(const Sprite &, const Transform &);
	void clear_screen();
	void present_screen();

private:
	SDL_Window * game_window = nullptr;
	SDL_Renderer * game_renderer = nullptr;
};

} // namespace crepe
