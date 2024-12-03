#include "../facade/SDLContext.h"
#include "../util/Log.h"

#include "Asset.h"
#include "Texture.h"
#include "types.h"

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

Texture::Texture(Texture && other) noexcept : texture(std::move(other.texture)) {}

Texture & Texture::operator=(Texture && other) noexcept {
	if (this != &other) {
		texture = std::move(other.texture);
	}
	return *this;
}

void Texture::load(const Asset & res) {
	SDLContext & ctx = SDLContext::get_instance();
	this->texture = ctx.texture_from_path(res.get_path());
}

ivec2 Texture::get_size() const {
	if (this->texture == nullptr) return {};
	return SDLContext::get_instance().get_size(*this);
}
