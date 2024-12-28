#pragma once

#include "CoinData.h"
#include "api/Scene.h"
#include "api/Script.h"
#include "api/Sprite.h"
#include "types.h"
#include <string>
#include <vector>

class CoinSystem {
public:
	void create_coins(crepe::Scene & scn);
	void add_location(const crepe::vec2& location);
	void remove_location(const std::string& name);
	void update(float position,crepe::RefVector<crepe::Sprite> coin_sprites,crepe::RefVector<crepe::CircleCollider> coin_colliders,crepe::RefVector<crepe::Metadata> coin_metadatas);
private:
	static constexpr float SPAWN_DISTANCE = 200;
	static constexpr float SPAWN_AREA = 50;
	static constexpr int MAXIMUM_AMOUNT = 100;
	static std::vector<CoinData> coin_locations;
};
