#include <SDL2/SDL_render.h>

#include "util/log.h"

#include "Asset.h"
#include "SdlContext.h"
#include "Texture.h"

using namespace crepe::api;
using namespace std;

Texture::Texture(unique_ptr<Asset> res) {
	dbg_trace();
	this->load(std::move(res));
}

Texture::Texture(const char * src) {
	dbg_trace();
	this->load(make_unique<Asset>(src));
}

Texture::~Texture() {
	dbg_trace();
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}
}

void Texture::load(unique_ptr<Asset> res) {
	SdlContext & ctx = SdlContext::get_instance();
	this->texture = ctx.texture_from_path(res->canonical());
}
