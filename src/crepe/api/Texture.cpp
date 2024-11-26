#include <SDL2/SDL_render.h>

#include "../facade/SDLContext.h"
#include "../util/Log.h"

#include "Asset.h"
#include "Texture.h"

using namespace crepe;
using namespace std;

Texture::Texture(const Asset & src) {
	dbg_trace();
	this->load(src);
}

Texture::~Texture() {
	dbg_trace();
	this->texture.reset();
}

void Texture::load(const Asset & res) {
	SDLContext & ctx = SDLContext::get_instance();
	this->texture = ctx.texture_from_path(res.get_path());
}

int Texture::get_width() const {
	if (this->texture == nullptr) return 0;
	return SDLContext::get_instance().get_width(*this);
}
int Texture::get_height() const {
	if (this->texture == nullptr) return 0;
	return SDLContext::get_instance().get_height(*this);
}
