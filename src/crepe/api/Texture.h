#pragma once

#include "Asset.h"
#include <SDL2/SDL_render.h>
#include <memory>

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
	SDL_Texture * m_texture = nullptr;

	friend class crepe::SdlContext;
};

} // namespace crepe::api
