#pragma once

#include <SDL2/SDL_render.h>
#include <memory>

#include "Asset.h"

namespace crepe {
class SdlContext;
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

	friend class crepe::SdlContext;
};

} // namespace crepe::api
