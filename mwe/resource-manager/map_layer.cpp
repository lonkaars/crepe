

#include "map_layer.h"
#include "TextureMap.h"
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>

MapLayer::MapLayer() {}

MapLayer::~MapLayer() { m_subsets.clear(); }

bool MapLayer::create(const tmx::Map & map, std::uint32_t layerIndex,
					  const std::vector<TextureMap *> & textures) {
	const auto & layers = map.getLayers();
	assert(layers[layerIndex]->getType() == tmx::Layer::Type::Tile);

	const auto & layer = layers[layerIndex]->getLayerAs<tmx::TileLayer>();
	const auto mapSize = map.getTileCount();
	const auto mapTileSize = map.getTileSize();
	const auto & tileSets = map.getTilesets();

	const auto tintColour = layer.getTintColour();
	const SDL_Colour vertColour
		= {tintColour.r, tintColour.g, tintColour.b, tintColour.a};

	for (auto i = 0u; i < tileSets.size(); ++i) {
		//check tile ID to see if it falls within the current tile set
		const auto & ts = tileSets[i];
		const auto & tileIDs = layer.getTiles();

		const auto texSize = textures[i]->getSize();
		const auto tileCountX = texSize.x / mapTileSize.x;
		const auto tileCountY = texSize.y / mapTileSize.y;

		const float uNorm = static_cast<float>(mapTileSize.x) / texSize.x;
		const float vNorm = static_cast<float>(mapTileSize.y) / texSize.y;

		std::vector<SDL_Vertex> verts;
		for (auto y = 0u; y < mapSize.y; ++y) {
			for (auto x = 0u; x < mapSize.x; ++x) {
				const auto idx = y * mapSize.x + x;
				if (idx < tileIDs.size() && tileIDs[idx].ID >= ts.getFirstGID()
					&& tileIDs[idx].ID
						   < (ts.getFirstGID() + ts.getTileCount())) {
					//tex coords
					auto idIndex = (tileIDs[idx].ID - ts.getFirstGID());
					float u = static_cast<float>(idIndex % tileCountX);
					float v = static_cast<float>(idIndex / tileCountY);
					u *= mapTileSize
							 .x; //TODO we should be using the tile set size, as this may be different from the map's grid size
					v *= mapTileSize.y;

					//normalise the UV
					u /= textures[i]->getSize().x;
					v /= textures[i]->getSize().y;

					//vert pos
					const float tilePosX
						= static_cast<float>(x) * mapTileSize.x;
					const float tilePosY
						= (static_cast<float>(y) * mapTileSize.y);

					//push back to vert array
					SDL_Vertex vert
						= {{tilePosX, tilePosY}, vertColour, {u, v}};
					verts.emplace_back(vert);
					vert = {{tilePosX + mapTileSize.x, tilePosY},
							vertColour,
							{u + uNorm, v}};
					verts.emplace_back(vert);
					vert = {{tilePosX, tilePosY + mapTileSize.y},
							vertColour,
							{u, v + vNorm}};
					verts.emplace_back(vert);

					vert = {{tilePosX, tilePosY + mapTileSize.y},
							vertColour,
							{u, v + vNorm}};
					verts.emplace_back(vert);
					vert = {{tilePosX + mapTileSize.x, tilePosY},
							vertColour,
							{u + uNorm, v}};
					verts.emplace_back(vert);
					vert
						= {{tilePosX + mapTileSize.x, tilePosY + mapTileSize.y},
						   vertColour,
						   {u + uNorm, v + vNorm}};
					verts.emplace_back(vert);
				}
			}
		}

		if (!verts.empty()) {
			m_subsets.emplace_back();
			m_subsets.back().texture = *textures[i];
			m_subsets.back().vertexData.swap(verts);
		}
	}

	return true;
}

void MapLayer::draw(SDL_Renderer * renderer) const {
	assert(renderer);
	for (const auto & s : m_subsets) {
		SDL_RenderGeometry(renderer, s.texture, s.vertexData.data(),
						   static_cast<std::int32_t>(s.vertexData.size()),
						   nullptr, 0);
	}
}
