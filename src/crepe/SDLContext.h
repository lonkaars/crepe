#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdint>

#include "AnimatorSystem.h"
#include "api/Camera.h"
#include "api/Sprite.h"
#include "api/Transform.h"

#include "RenderSystem.h"
#include "api/loopManager.h"


typedef SDL_Keycode CREPE_KEYCODES;


namespace crepe::api {
class Texture;
}

namespace crepe {

class SDLContext {

public:
	// singleton
	static SDLContext & get_instance();
	SDLContext(const SDLContext &) = delete;
	SDLContext(SDLContext &&) = delete;
	SDLContext & operator=(const SDLContext &) = delete;
	SDLContext & operator=(SDLContext &&) = delete;

private:
	friend class api::LoopManager;
	void handle_events(bool & running);

private:
	friend class AnimatorSystem;
	const uint64_t get_ticks() const;

private:
	SDLContext();
	virtual ~SDLContext();

private:
	friend class api::Texture;
	SDL_Texture * texture_from_path(const char *);

private:
	friend class RenderSystem;
	void draw(const api::Sprite &, const api::Transform &, const api::Camera&);
	void clear_screen();
	void present_screen();
	void camera(const api::Camera&);

private:
	SDL_Window * game_window = nullptr;
	SDL_Renderer * game_renderer = nullptr;
	SDL_Rect viewport = {0,0,640,480};
};

} // namespace crepe
