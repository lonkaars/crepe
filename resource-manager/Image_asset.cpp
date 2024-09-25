

#include "Image_asset.h"
#include <SDL_image.h>
#include <SDL_surface.h>



Texture::Texture(const std::string& path){
	m_surface = IMG_Load(path.c_str());
}

void Texture::setTexture(SDL_Renderer& renderer){
	m_texture = SDL_CreateTextureFromSurface(&renderer, m_surface);
}

Texture::~Texture(){
	if (m_surface) {
		SDL_FreeSurface(m_surface);
	}

	if(m_texture){
		SDL_DestroyTexture(m_texture);
	}
}

SDL_Surface* Texture::getSurface() const {
	return m_surface;
}

SDL_Texture* Texture::getTexture() const{
	return m_texture;
}
