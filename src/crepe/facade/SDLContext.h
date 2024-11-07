#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include "../api/Sprite.h"
#include "../api/Transform.h"
#include "api/Camera.h"
#include "../api/loopManager.h"

typedef SDL_Keycode CREPE_KEYCODES;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


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

private:
        friend class LoopManager;
        void handle_events(bool & running);

private:
        friend class AnimatorSystem;
        const uint64_t get_ticks() const;

private:
        SDLContext();
        virtual ~SDLContext();

private:
        friend class Texture;
        SDL_Texture * texture_from_path(const char *);
		int get_width(const Texture&);
		int get_height(const Texture&);

private:
        friend class RenderSystem;
        void draw(const Sprite &, const Transform &, const Camera&);
        void clear_screen();
        void present_screen();
        void camera(const Camera&);

private:
        SDL_Window * game_window = nullptr;
        SDL_Renderer * game_renderer = nullptr;
        SDL_Rect viewport = {0,0,640,480};
};


} // namespace crepe
