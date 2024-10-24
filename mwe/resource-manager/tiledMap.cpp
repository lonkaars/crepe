

#include "tiledMap.h"
#include "TextureMap.h"
#include "map_layer.h"
#include <SDL_render.h>
#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
#include <tmxlite/Layer.hpp>
#include <tmxlite/Map.hpp>

TiledMap::TiledMap(const std::string & content) {
	if (m_TmxMap.loadFromString(content, "../../asset/tiled/")) {
		std::cout << "Map loaded correctly " << std::endl;
	}
}

TiledMap::~TiledMap() {
	for (const auto & r : m_MapTextures) {
		delete r;
	}
	m_MapTextures.clear();

	for (const auto & m : m_RenderLayers) {
		delete m;
	}
	m_RenderLayers.clear();
}

void TiledMap::SetRenderer(SDL_Renderer & renderer) {
	this->m_Renderer = &renderer;
	this->SetMapTextures();
	this->SetMapLayers();
}

void TiledMap::draw() const {
	for (const auto & l : m_RenderLayers) {
		l->draw(m_Renderer);
	}
}

void TiledMap::SetMapTextures() {
	const auto & tileSets = m_TmxMap.getTilesets();
	assert(~tileSets.empty());

	std::cout << "Processing SetMapTextures " << std::endl;

	for (const auto & ts : tileSets) {
		m_MapTextures.emplace_back(new TextureMap);
		if (!m_MapTextures.back()->loadFromFile(ts.getImagePath(),
												m_Renderer)) {
			std::cerr << "Failed opening " << ts.getImagePath() << "\n";
		}
	}
}

void TiledMap::SetMapLayers() {
	const auto & mapLayers = m_TmxMap.getLayers();

	std::cout << "Processing SetMapLayers " << std::endl;
	for (auto i = 0u; i < mapLayers.size(); ++i) {
		if (mapLayers[i]->getType() == tmx::Layer::Type::Tile) {
			m_RenderLayers.emplace_back(new MapLayer);
			m_RenderLayers.back()->create(this->m_TmxMap, i,
										  this->m_MapTextures);
		}
	}
}
