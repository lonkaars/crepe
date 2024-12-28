#include "CoinSystem.h"
#include "CoinSubScene.h"
#include "api/CircleCollider.h"
#include "api/Metadata.h"
#include "api/Script.h"
#include "api/Sprite.h"
#include "api/Transform.h"
#include "types.h"

using namespace crepe;
using namespace std;

std::vector<CoinData> CoinSystem::coin_locations;

void CoinSystem::create_coins(crepe::Scene & scn) {
	CoinSubScene coin;
	while(coin.create(scn) < this->MAXIMUM_AMOUNT);
}

void CoinSystem::add_location(const crepe::vec2& location){
	coin_locations.push_back(CoinData(location));
}

void CoinSystem::remove_location(const std::string& name){
	auto it = std::find_if(coin_locations.begin(), coin_locations.end(),
				[&name](const CoinData& data) {
					return data.name == name;
				});

	// If a match is found, erase
	if (it != coin_locations.end()) {
		coin_locations.erase(it);
	}
}


void CoinSystem::update(float position, RefVector<Sprite> coin_sprites, RefVector<CircleCollider> coin_colliders, RefVector<Metadata> coin_metadatas) {
	for (auto& coin : coin_locations) {
		if (!coin.active) {
			if (coin.start_location.x > SPAWN_DISTANCE + position && coin.start_location.x < SPAWN_AREA + SPAWN_DISTANCE + position) {
					
				// Local variables to hold the matching coin data
				Metadata* coin_metadata = nullptr;
				CircleCollider* coin_collider = nullptr;
				
				// Iterate over the sprites to find the matching one
				for (Sprite& coin_sprite : coin_sprites) {
					if (!coin_sprite.active) {
						// Find the matching Metadata
						for (Metadata& coin_metadata_unkown : coin_metadatas) {
							if (coin_metadata_unkown.game_object_id == coin_sprite.game_object_id) {
								coin_metadata = &coin_metadata_unkown;
								// No need to continue searching
								break; 
							}
						}
							
						// Find the matching CircleCollider
						for (CircleCollider& coin_collider_unkown : coin_colliders) {
							if (coin_collider_unkown.game_object_id == coin_sprite.game_object_id) {
								coin_collider = &coin_collider_unkown;
								// No need to continue searching
								break;
							}
						}

						// If we found both the metadata and collider, activate the coin
						if (coin_metadata && coin_collider) {
							coin.name = coin_metadata->name;
							coin.active = true;
							coin_sprite.active = true;
							coin_collider->active = true;
							break;
						}
					}
				}
			}
		}
	}
}

