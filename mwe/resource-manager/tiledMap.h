

#include "TextureMap.h"
#include "map_layer.h"
#include <string>
#include <tmxlite/Map.hpp>
#include <vector>

class TiledMap {

public:
	TiledMap(const std::string &);
	~TiledMap();

	void SetRenderer(SDL_Renderer &);
	void draw() const;

private:
	void SetMapTextures();
	void SetMapLayers();

private:
	tmx::Map m_TmxMap;
	std::vector<TextureMap *> m_MapTextures;
	std::vector<MapLayer *> m_RenderLayers;

	SDL_Renderer * m_Renderer;
};
