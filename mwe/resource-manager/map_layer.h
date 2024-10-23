#pragma once

#include "TextureMap.h"
#include <SDL_render.h>
#include <tmxlite/Map.hpp>

class MapLayer final {

public:
	explicit MapLayer();
	~MapLayer();

	bool create(const tmx::Map &, std::uint32_t index,
				const std::vector<TextureMap *> & textures);
	void draw(SDL_Renderer *) const;

private:
	struct subset final {
		std::vector<SDL_Vertex> vertexData;
		SDL_Texture * texture = nullptr;
	};
	std::vector<subset> m_subsets;
};
