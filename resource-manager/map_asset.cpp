



#include "map_asset.h"
#include "TextureMap.h"
#include "map_layer.h"
#include <SDL_render.h>
#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
#include <tmxlite/Layer.hpp>
#include <tmxlite/Map.hpp>


Map::Map(const std::string& path){
	if(m_Map.load(path)){
		std::cout << "Map loaded correctly " << std::endl;
	}
}

Map::~Map(){
	for(const auto& r : m_MapTextures){
		delete r;
	}
	m_MapTextures.clear();

	for(const auto& m : m_RenderLayers){
		delete m;
	}
	m_RenderLayers.clear();
}


void Map::SetRenderer(SDL_Renderer& renderer){
	this->m_Renderer = &renderer;
	this->SetMapTextures();
	this->SetMapLayers();
}

void Map::draw() const{
	for(const auto& l : m_RenderLayers){
		l->draw(m_Renderer);
	}
}

void Map::SetMapTextures(){
	const auto& tileSets = m_Map.getTilesets();
	assert(~tileSets.empty());

	for (const auto& ts : tileSets ) {
		m_MapTextures.emplace_back(new TextureMap);
		if(!m_MapTextures.back()->loadFromFile(ts.getImagePath(), m_Renderer)){
			std::cerr << "Failed opening " << ts.getImagePath() << "\n";
		}
	}
}

void Map::SetMapLayers(){
	const auto& mapLayers = m_Map.getLayers();

	for(auto i = 0u; i < mapLayers.size(); ++i){
		if (mapLayers[i]->getType() == tmx::Layer::Type::Tile) {
			m_RenderLayers.emplace_back(new MapLayer);		
			m_RenderLayers.back()->create(this->m_Map, i, this->m_MapTextures);
		}
	}
}
