

#include "spritesheet.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "api/Resource.h"
#include "facade/SdlContext.h"
#include <memory>


using namespace crepe::api;

Spritesheet::Spritesheet(const char* src, const int row, const int col){
	this->load(std::make_unique<api::Resource>(src), row, col);
}

Spritesheet::Spritesheet(std::unique_ptr<api::Resource> res, const int row, const int col){
	this->load(std::move(res), row, col);
}

Spritesheet::~Spritesheet(){

	if (this->m_spritesheet) {
		SDL_DestroyTexture(this->m_spritesheet);
	}
}

void Spritesheet::select_sprite(const int x, const int y){
	m_clip.x = x * m_clip.w;
	m_clip.y = y * m_clip.h;
}

void Spritesheet::load(std::unique_ptr<api::Resource> res, const int row, const int col){
	auto& ctx = SdlContext::get_instance();

	this->m_spritesheet = ctx.setTextureFromPath(res->canonical(), this->m_clip, row, col);
}

