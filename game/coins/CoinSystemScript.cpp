#include "CoinSystemScript.h"
#include "CoinSystem.h"
#include "api/CircleCollider.h"
#include "api/Metadata.h"
#include "api/Sprite.h"
#include "api/Transform.h"

using namespace crepe;
using namespace std;

std::vector<CoinData> CoinSystemScript::coin_locations;

void CoinSystemScript::init() {
	this->add_location(vec2{1500,-30});
	this->add_location(vec2{1500,0});
	this->add_location(vec2{1500,30});
	this->add_location(vec2{1500,60});
	this->add_location(vec2{1550,-30});
	this->add_location(vec2{1550,0});
	this->add_location(vec2{1550,30});
	this->add_location(vec2{1550,60});

	this->add_location(vec2{2500,-30});
	this->add_location(vec2{2500,0});
	this->add_location(vec2{2500,30});
	this->add_location(vec2{2500,60});
	this->add_location(vec2{2550,-30});
	this->add_location(vec2{2550,0});
	this->add_location(vec2{2550,30});
	this->add_location(vec2{2550,60});
	this->add_location(vec2{2600,-30});
	this->add_location(vec2{2600,0});
	this->add_location(vec2{2600,30});
	this->add_location(vec2{2600,60});
	this->add_location(vec2{2650,-30});
	this->add_location(vec2{2650,0});
	this->add_location(vec2{2650,30});
	this->add_location(vec2{2650,60});
	this->add_location(vec2{2700,-30});
	this->add_location(vec2{2700,0});
	this->add_location(vec2{2700,30});
	this->add_location(vec2{2700,60});
	this->add_location(vec2{2750,-30});
	this->add_location(vec2{2750,0});
	this->add_location(vec2{2750,30});
	this->add_location(vec2{2750,60});
	this->add_location(vec2{2800,-30});
	this->add_location(vec2{2800,0});
	this->add_location(vec2{2800,30});
	this->add_location(vec2{2800,60});
	this->add_location(vec2{2850,-30});
	this->add_location(vec2{2850,0});
	this->add_location(vec2{2850,30});
	this->add_location(vec2{2850,60});
}

void CoinSystemScript::add_location(const crepe::vec2& location){
	coin_locations.push_back(CoinData(location));
}

void CoinSystemScript::despawn_coins() {
	// Get the current x-position of the CoinSystem's Transform component
	float position = this->get_component<Transform>().position.x;

	// Retrieve all active coin sprites tagged as "coin"
	RefVector<Sprite> coin_sprites = this->get_components_by_tag<Sprite>("coin");

	for (Sprite& coin_sprite : coin_sprites) {
		if (!coin_sprite.active) continue; // Skip inactive sprites

		// Retrieve the corresponding Transform, Metadata, and CircleCollider components
		Transform& coin_transform = this->get_components_by_id<Transform>(coin_sprite.game_object_id).front().get();
		Metadata& coin_metadata = this->get_components_by_id<Metadata>(coin_sprite.game_object_id).front().get();
		CircleCollider& coin_collider = this->get_components_by_id<CircleCollider>(coin_sprite.game_object_id).front().get();

		// Check if the coin is out of bounds based on DESPAWN_DISTANCE
		if (coin_transform.position.x < position - this->DESPAWN_DISTANCE) {
			// Find the coin in the coin_locations vector using its name
			auto it = std::find_if(
				coin_locations.begin(),
				coin_locations.end(),
				[&coin_metadata](const CoinData& data) {
						return data.name == coin_metadata.name;
				}
			);

			// If a match is found, erase it from coin_locations
			if (it != coin_locations.end()) {
				coin_locations.erase(it);
				coin_sprite.active = false;
				coin_collider.active = false;
			}
		}
	}
}

void CoinSystemScript::spawn_coins(){
	// Get the current x-position of the CoinSystem's Transform component
	float position = this->get_component<Transform>().position.x;

	// Iterate through the list of coin locations
	for (auto& coin : coin_locations) {
		// Skip this coin if it is already active
		if (coin.active)continue;
		// Skip this coin if it is not within the defined spawn area
		if (coin.start_location.x < this->SPAWN_DISTANCE + position || coin.start_location.x > this->SPAWN_AREA + this->SPAWN_DISTANCE + position) continue;
		
		// Retrieve all sprites tagged as "coin"
		RefVector<Sprite> coin_sprites = this->get_components_by_tag<Sprite>("coin");

		// Check for an available (inactive) coin sprite
		for (Sprite& coin_sprite : coin_sprites) {
			// Skip this sprite if it is already active
			if (coin_sprite.active) continue;

			// Found an available (inactive) coin sprite
			// Retrieve its associated components
			Transform & coin_transform = this->get_components_by_id<Transform>(coin_sprite.game_object_id).front().get();
			Metadata & coin_metadata = this->get_components_by_id<Metadata>(coin_sprite.game_object_id).front().get();
			CircleCollider & coin_collider = this->get_components_by_id<CircleCollider>(coin_sprite.game_object_id).front().get();
			
			// Assign data and set active
			coin.name = coin_metadata.name;
			coin.active = true;
			coin_sprite.active = true;
			coin_collider.active = true;
			coin_transform.position = coin.start_location;

			// Break out of the inner loop since we've assigned this coin to an available sprite	
			break;
		}
	}
}

void CoinSystemScript::frame_update(crepe::duration_t dt)
{
	this->despawn_coins();
	this->spawn_coins();	
}



