#pragma once




#include "Resource.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include <memory>


namespace crepe::api {

class Spritesheet{

public:
	Spritesheet(const char * src, const int row , const int col);
	Spritesheet(std::unique_ptr<api::Resource> res, const int row, const int col);
	~Spritesheet();

	void select_sprite(const int x, const int y);
	void draw_selected_sprite(const int x, const int y);
private:
	void load(std::unique_ptr<api::Resource> res, const int row, const int col);;
	SDL_Texture* get_texture() const;



private:

	SDL_Texture* m_spritesheet;
	SDL_Rect m_clip;

	friend class SdlContext;
};

}

