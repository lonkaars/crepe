
#include "Coin.h"
#include "api/Asset.h"
#include "api/AudioSource.h"
#include "api/BehaviorScript.h"
#include "system/CollisionSystem.h"
#include "types.h"

#include <crepe/api/Animator.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <iostream>

using namespace crepe;
using namespace std;

class CoinPickup : public Script {
	bool on_collision(const CollisionEvent & ev) {
		const auto & info = ev.info;
		cout << info.this_metadata.game_object_id << " " << info.other_metadata.name << endl;
		return true;
	}
	void init() {
		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->on_collision(ev); });
	}
};

Coin::Coin(GameObject & coin, const vec2 & start_pos) {
	Asset asset_coin{"assets/Entities/coin1_TVOS.png"};
	Asset asset_coin_pickup_audio{"assets/SFX/Obstacle/Coin/coin_pickup_1.mp3"};

	vec2 size = {20, 20};
	this->coin_sprite = coin.add_component<Sprite>(asset_coin, Sprite::Data{
																   .sorting_in_layer = 10,
																   .order_in_layer = 10,
																   .size = size,
															   });

	coin.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 10,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.collision_layers = {0},
	});

	coin.add_component<CircleCollider>(size.x / 2);
	coin.add_component<Animator>(this->coin_sprite, ivec2{32, 32}, uvec2{8, 1},
								 Animator::Data{
									 .looping = true,
								 });
	this->coin_pickup_audio = coin.add_component<AudioSource>(asset_coin_pickup_audio);
	coin.add_component<BehaviorScript>().set_script<CoinPickup>();
}

void Coin::pickup() {
	//this->coin_sprite->active = false;
	//this->coin_pickup_audio->play();
}
