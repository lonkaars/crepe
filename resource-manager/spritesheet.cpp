

#include "spritesheet.h"
#include "Image_asset.h"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <cstdlib>
#include <string>


SpriteSheet::SpriteSheet(const std::string& path){
	m_spritesheet = new Texture(path);
}

void SpriteSheet::set_spritesheet_data(SDL_Renderer& renderer, const int row, const int column){
	m_spritesheet->setTexture(renderer);
	m_clip.w = m_spritesheet->getSurface()->w / column;
	m_clip.h = m_spritesheet->getSurface()->h / row;
}

SpriteSheet::~SpriteSheet(){
	delete m_spritesheet;
}

void SpriteSheet::select_sprite(const int x, const int y){
	m_clip.x = x * m_clip.w;
	m_clip.y = y * m_clip.h;
}

void SpriteSheet::draw_selected_sprite(SDL_Renderer* window_surface, SDL_Rect* position){
	SDL_RenderCopy(window_surface, m_spritesheet->getTexture(), &m_clip, position);
}


SDL_Surface* SpriteSheet::getSurface() const {
	return m_spritesheet->getSurface();
}
