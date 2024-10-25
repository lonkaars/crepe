#pragma once

// FIXME: this header can't be included because this is an API header, and SDL2
// development headers won't be bundled with crepe. Why is this facade in the
// API namespace?
#include <SDL2/SDL_render.h>
#include <memory>

#include "Asset.h"

namespace crepe {
class SDLContext;
}

namespace crepe::api {

class Texture {

public:
	Texture(const char * src);
	Texture(std::unique_ptr<Asset> res);
	~Texture();

private:
	void load(std::unique_ptr<Asset> res);

private:
	SDL_Texture * texture = nullptr;

	friend class crepe::SDLContext;
};

} // namespace crepe::api
