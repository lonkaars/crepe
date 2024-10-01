

#include "SdlContext.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

using namespace crepe;


SdlContext& SdlContext::get_instance(){
	static SdlContext instance;
	return instance;
}


SdlContext::SdlContext(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    m_game_window = SDL_CreateWindow("Crepe Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!m_game_window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    m_game_renderer = SDL_CreateRenderer(m_game_window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_game_renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_game_window);
        return;
    }

	IMG_Init(IMG_INIT_PNG);
}

SdlContext::~SdlContext(){
	if(m_game_renderer)
		SDL_DestroyRenderer(m_game_renderer);

	if (m_game_window) {
		SDL_DestroyWindow(m_game_window);
	}
	IMG_Quit();
}


SDL_Texture* SdlContext::setTextureFromPath(const char* path){
	SDL_Surface* tmp = IMG_Load(path);
	SDL_Texture* CreatedTexture = SDL_CreateTextureFromSurface(m_game_renderer, tmp);
	SDL_FreeSurface(tmp);

	return CreatedTexture;
}
