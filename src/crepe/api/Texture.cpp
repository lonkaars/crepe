#include "../util/Log.h"

#include "Asset.h"
#include "Resource.h"
#include "Texture.h"
#include "types.h"
#include <utility>

using namespace crepe;
using namespace std;

Texture::Texture(const Asset & src) : Resource(src) {
	dbg_trace();
}

Texture::~Texture() {
	dbg_trace();
	this->texture.reset();
}

void Texture::load(std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> texture) {
	this->texture = std::move(texture);
	this->loaded = true;
}

ivec2 Texture::get_size() const {
	if (this->texture == nullptr) return {};
	return {};
}
