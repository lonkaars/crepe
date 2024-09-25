#pragma once


#include "TextureMap.h"
#include "map_layer.h"
#include "resource.h"
#include <string>
#include <tmxlite/Map.hpp>
#include <vector>


class Map : public Resource {

public:
	Map(const std::string& path);
	~Map();

	void SetRenderer(SDL_Renderer&);
	void draw() const;


private:
	void SetMapTextures();
	void SetMapLayers();


private:
	tmx::Map m_Map;
	std::vector<TextureMap*> m_MapTextures;
	std::vector<MapLayer*> m_RenderLayers;

	SDL_Renderer* m_Renderer;


};
