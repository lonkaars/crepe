#pragma once




#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>
class SpriteSheet{


public:
	SpriteSheet(const std::string& path, SDL_Renderer& renderer, const int row, const int column);
	~SpriteSheet();


	void select_sprite(const int x, const int y);
	void draw_selected_sprite(SDL_Renderer* window_surface, SDL_Rect* position);
	SDL_Surface* getSurface() const;

private:
	SDL_Rect m_clip;
	SDL_Surface* m_spritesheet_image;
	SDL_Texture * texture;

};
