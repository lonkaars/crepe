#include <SDL2/SDL_render.h>

#include "../facade/SDLContext.h"
#include "../util/log.h"
#include "Asset.h"

#include "Texture.h"

using namespace crepe;
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
	SDLContext & ctx = SDLContext::get_instance();
	this->texture = ctx.texture_from_path(res->canonical());
}

int Texture::get_width() const{
	if (this->texture) {
		return SDLContext::get_instance().get_width(*this);
	}
	else {
		return 0;
	}
}
int Texture::get_height() const{
	if (this->texture) {
		return SDLContext::get_instance().get_height(*this);
	}
	else {
		return 0;
	}
}
