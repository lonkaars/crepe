#pragma once

// FIXME: this header can't be included because this is an API header, and SDL2
// development headers won't be bundled with crepe. Why is this facade in the
// API namespace?

#include <SDL2/SDL_render.h>
#include <memory>

#include "Asset.h"

namespace crepe {

class SDLContext;
class Animator;

class Texture {

public:
	Texture(const char * src);
	Texture(std::unique_ptr<Asset> res);
	~Texture();

	int get_width() const;
	int get_height() const;

private:
	void load(std::unique_ptr<Asset> res);

private:
	SDL_Texture * texture = nullptr;

	friend class SDLContext;
	friend class Animator;
};

} // namespace crepe
