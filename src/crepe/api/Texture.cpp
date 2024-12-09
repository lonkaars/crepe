#include "../util/Log.h"
#include "manager/Mediator.h"
#include "facade/SDLContext.h"

#include "Asset.h"
#include "Resource.h"
#include "Texture.h"
#include "types.h"

using namespace crepe;
using namespace std;

Texture::Texture(const Asset & src, Mediator & mediator) : Resource(src, mediator){
	dbg_trace();
	SDLContext & ctx = mediator.sdl_context;
	this->texture = ctx.texture_from_path(src.get_path());
	this->size = ctx.get_size(*this);
	this->aspect_ratio = static_cast<float>(this->size.x) / this->size.y;
}

Texture::~Texture() {
	dbg_trace();
	this->texture.reset();
}

const ivec2 & Texture::get_size() const noexcept{
	return this->size;
}
const float & Texture::get_ratio() const noexcept{
	return this->aspect_ratio;
}

SDL_Texture * Texture::get_img() const noexcept{
	return this->texture.get();
}
