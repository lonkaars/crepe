

#include "Asset.h"
#include "SdlContext.h"
#include "util/log.h"

#include "Texture.h"
#include <SDL2/SDL_render.h>

using namespace crepe::api;

Texture::Texture(std::unique_ptr<Asset> res) {
	dbg_trace();
	this->load(std::move(res));
}

Texture::Texture(const char * src) {
	dbg_trace();
	this->load(std::make_unique<Asset>(src));
}

Texture::~Texture() {
	dbg_trace();
	if (this->m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
	}
}
void Texture::load(std::unique_ptr<Asset> res) {
	SdlContext & ctx = SdlContext::get_instance();
	m_texture = ctx.texture_from_path(res->canonical());

}
