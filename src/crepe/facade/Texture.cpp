

#include "util/log.h"

#include "Texture.h"
#include "SdlContext.h"
#include <SDL2/SDL_render.h>

using namespace crepe;

Texture::Texture(std::unique_ptr<api::Resource> res) {
	dbg_trace();
	this->load(std::move(res));
}

Texture::Texture(const char * src) {
	dbg_trace();
	this->load(std::make_unique<api::Resource>(src));
}

Texture::~Texture(){
	dbg_trace();
	if(this->m_texture){
		SDL_DestroyTexture(m_texture);
	}
}
void Texture::load(std::unique_ptr<api::Resource> res) {
	dbg_trace();
	SdlContext& ctx = SdlContext::get_instance();
	m_texture = ctx.setTextureFromPath(res->canonical());
}

SDL_Texture* Texture::get_texture() const{
	return m_texture;
}
