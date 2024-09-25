#pragma once




#include "Image_asset.h"
#include "resource.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <string>


class SpriteSheet : public Resource{


public:
	SpriteSheet(const std::string& path);
	~SpriteSheet();

	void set_spritesheet_data(SDL_Renderer& renderer, const int row, const int column);


	void select_sprite(const int x, const int y);
	void draw_selected_sprite(SDL_Renderer* window_surface, SDL_Rect* position);
	SDL_Surface* getSurface() const;

private:
	SDL_Rect m_clip;
	Texture* m_spritesheet;
};
