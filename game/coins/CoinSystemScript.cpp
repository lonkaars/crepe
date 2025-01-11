#include "CoinSystemScript.h"

#include <random>

#include <crepe/api/CircleCollider.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>

using namespace crepe;
using namespace std;

void CoinSystemScript::init() { engine.seed(rd()); }

void CoinSystemScript::add_location(const crepe::vec2 & location) {
	coin_locations.push_back(CoinData(location));
}

float CoinSystemScript::preset_1(const vec2 & begin_position) {
	vec2 top = {begin_position.x, begin_position.y - (this->ROW_OFFSET_1)};
	vec2 bottom = {begin_position.x, begin_position.y + (this->ROW_OFFSET_1)};

	// Add locations for the top row
	for (int i = 0; i < COLUM_AMOUNT_1; ++i) {
		add_location(top);
		top.x += this->COLUM_OFFSET_1;
	}

	// Add locations for the bottom row
	bottom.x += this->COLUM_OFFSET_1 * COLUM_AMOUNT_1;
	for (int i = 0; i < COLUM_AMOUNT_1; ++i) {
		add_location(bottom);
		bottom.x += this->COLUM_OFFSET_1;
	}

	// Add locations for the next set of the top row
	top.x += this->COLUM_OFFSET_1 * COLUM_AMOUNT_1;
	for (int i = 0; i < COLUM_AMOUNT_1; ++i) {
		add_location(top);
		top.x += this->COLUM_OFFSET_1;
	}

	// Add locations for the next set of the bottom row
	bottom.x += this->COLUM_OFFSET_1 * COLUM_AMOUNT_1;
	for (int i = 0; i < COLUM_AMOUNT_1; ++i) {
		add_location(bottom);
		bottom.x += this->COLUM_OFFSET_1;
	}

	return bottom.x - begin_position.x;
}

float CoinSystemScript::preset_2(const vec2 & begin_position) {
	vec2 top
		= {begin_position.x + this->COLUM_OFFSET_2, begin_position.y - this->ROW_OFFSET_2};
	vec2 middle = begin_position;
	vec2 bottom
		= {begin_position.x + this->COLUM_OFFSET_2, begin_position.y + this->ROW_OFFSET_2};

	// Add locations for the next set of the bottom row
	for (int i = 0; i < COLUM_AMOUNT_2 - 2; ++i) {
		add_location(bottom);
		bottom.x += this->COLUM_OFFSET_2;
	}

	// Add locations for the next set of the middle row
	for (int i = 0; i < COLUM_AMOUNT_2; ++i) {
		add_location(middle);
		middle.x += this->COLUM_OFFSET_2;
	}

	// Add locations for the next set of the top row
	for (int i = 0; i < COLUM_AMOUNT_2 - 2; ++i) {
		add_location(top);
		top.x += this->COLUM_OFFSET_2;
	}

	return middle.x - begin_position.x;
}

float CoinSystemScript::preset_3(const vec2 & begin_position) {
	vec2 location = {begin_position.x, begin_position.y - (this->ROW_OFFSET_3)};

	// Add locations for the top row
	for (int i = 0; i < COLUM_AMOUNT_3; ++i) {
		add_location(location);
		location.x += this->COLUM_OFFSET_3;
	}

	// Add locations for the bottom row
	location.y += this->ROW_OFFSET_3;
	location.x += this->COLUM_OFFSET_3;
	for (int i = 0; i < COLUM_AMOUNT_3; ++i) {
		add_location(location);
		location.x += this->COLUM_OFFSET_3;
	}

	// Add locations for the next set of the top row
	location.y += this->ROW_OFFSET_3;
	location.x += this->COLUM_OFFSET_3;
	for (int i = 0; i < COLUM_AMOUNT_3; ++i) {
		add_location(location);
		location.x += this->COLUM_OFFSET_3;
	}

	return location.x - begin_position.x;
}

float CoinSystemScript::preset_4(const vec2 & begin_position) {
	vec2 location = {begin_position.x, begin_position.y + (this->ROW_OFFSET_4)};

	// Add locations for the top row
	for (int i = 0; i < COLUM_AMOUNT_4; ++i) {
		add_location(location);
		location.x += this->COLUM_OFFSET_4;
	}

	// Add locations for the bottom row
	location.y -= this->ROW_OFFSET_4;
	location.x += this->COLUM_OFFSET_4;
	for (int i = 0; i < COLUM_AMOUNT_4; ++i) {
		add_location(location);
		location.x += this->COLUM_OFFSET_4;
	}

	// Add locations for the next set of the top row
	location.y -= this->ROW_OFFSET_4;
	location.x += this->COLUM_OFFSET_4;
	for (int i = 0; i < COLUM_AMOUNT_4; ++i) {
		add_location(location);
		location.x += this->COLUM_OFFSET_4;
	}

	return location.x - begin_position.x;
}

float CoinSystemScript::preset_5(const vec2 & begin_position) {
	vec2 location = {begin_position.x, begin_position.y - ROW_OFFSET_5 / 2};
	for (int i = 0; i < COLUM_AMOUNT_5; ++i) {
		add_location(location);
		location.x += this->COLUM_OFFSET_5;
	}
	return location.x - begin_position.x;
}

void CoinSystemScript::frame_update(crepe::duration_t dt) {
	this->despawn_coins();
	this->generate_locations();
	this->spawn_coins();
}

void CoinSystemScript::despawn_coins() {
	// Get the current x-position of the CoinSystem's Transform component
	float position = this->get_component<Transform>().position.x;

	// Retrieve all active coin sprites tagged as "coin"
	RefVector<Sprite> coin_sprites = this->get_components_by_tag<Sprite>("coin");

	for (Sprite & coin_sprite : coin_sprites) {
		if (!coin_sprite.active) continue; // Skip inactive sprites

		// Retrieve the corresponding Transform, Metadata, and CircleCollider components
		Transform & coin_transform
			= this->get_components_by_id<Transform>(coin_sprite.game_object_id).front().get();
		Metadata & coin_metadata
			= this->get_components_by_id<Metadata>(coin_sprite.game_object_id).front().get();
		CircleCollider & coin_collider
			= this->get_components_by_id<CircleCollider>(coin_sprite.game_object_id)
				  .front()
				  .get();

		// Check if the coin is out of bounds based on DESPAWN_DISTANCE
		if (coin_transform.position.x < position - this->DESPAWN_DISTANCE) {
			// Find the coin in the coin_locations vector using its name
			auto it = std::find_if(
				coin_locations.begin(), coin_locations.end(),
				[&coin_metadata](const CoinData & data) {
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

void CoinSystemScript::spawn_coins() {
	// Get the current x-position of the CoinSystem's Transform component
	float position = this->get_component<Transform>().position.x;

	// Iterate through the list of coin locations
	for (auto & coin : coin_locations) {
		// Skip this coin if it is already active
		if (coin.active) continue;
		// Skip this coin if it is not within the defined spawn area
		if (coin.start_location.x < this->SPAWN_DISTANCE + position
			|| coin.start_location.x > this->SPAWN_AREA + this->SPAWN_DISTANCE + position)
			continue;

		// Retrieve all sprites tagged as "coin"
		RefVector<Sprite> coin_sprites = this->get_components_by_tag<Sprite>("coin");

		// Check for an available (inactive) coin sprite
		for (Sprite & coin_sprite : coin_sprites) {
			// Skip this sprite if it is already active
			if (coin_sprite.active) continue;
			if (coin_sprite.data.order_in_layer == 1) {
				coin_sprite.active = false;
				continue;
			}

			// Found an available (inactive) coin sprite
			// Retrieve its associated components
			Transform & coin_transform
				= this->get_components_by_id<Transform>(coin_sprite.game_object_id)
					  .front()
					  .get();
			Metadata & coin_metadata
				= this->get_components_by_id<Metadata>(coin_sprite.game_object_id)
					  .front()
					  .get();
			CircleCollider & coin_collider
				= this->get_components_by_id<CircleCollider>(coin_sprite.game_object_id)
					  .front()
					  .get();

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

void CoinSystemScript::generate_locations() {
	float position = this->get_component<Transform>().position.x;
	if (position + SPAWN_DISTANCE + SYSTEM_POSITION_OFFSET < this->system_position) return;

	std::discrete_distribution<int> dist(weights.begin(), weights.end());
	int selected_index = dist(engine);

	std::uniform_real_distribution<float> space_dist(SPAWN_SPACING_MIN, SPAWN_SPACING_MAX);
	float spacing = space_dist(engine);

	// Call the corresponding function and return the new x position
	this->system_position += functions[selected_index]({this->system_position, 0});
	this->system_position += spacing;
}
