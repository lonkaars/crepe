

#include "spritesheet.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <cstdlib>
#include <string>


SpriteSheet::SpriteSheet(const std::string& path, SDL_Renderer& renderer, const int row, const int column){
	m_spritesheet_image = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(&renderer, m_spritesheet_image);
	m_clip.w = m_spritesheet_image->w / column;
	m_clip.h = m_spritesheet_image->h / row;

}

SpriteSheet::~SpriteSheet(){
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(m_spritesheet_image);
}

void SpriteSheet::select_sprite(const int x, const int y){
	m_clip.x = x * m_clip.w;
	m_clip.y = y * m_clip.h;
}

void SpriteSheet::draw_selected_sprite(SDL_Renderer* window_surface, SDL_Rect* position){
	SDL_RenderCopy(window_surface, texture, &m_clip, position);
}


SDL_Surface* SpriteSheet::getSurface() const {
	return m_spritesheet_image;
}
