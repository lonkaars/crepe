#include "../util/Log.h"

#include "Asset.h"
#include "Resource.h"
#include "Texture.h"
#include "facade/SDLContext.h"
#include "manager/Mediator.h"
#include "types.h"

using namespace crepe;
using namespace std;

Texture::Texture(const Asset & src, Mediator & mediator) : Resource(src, mediator) {
	dbg_trace();
	SDLContext & ctx = mediator.sdl_context;
	this->texture = ctx.texture_from_path(src.get_path());
	this->size = ctx.get_size(*this);
}

Texture::~Texture() {
	dbg_trace();
	this->texture.reset();
}
