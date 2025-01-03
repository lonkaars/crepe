#include "CoinSubScene.h"
#include "api/Animator.h"
#include "api/BehaviorScript.h"
#include "api/CircleCollider.h"
#include "api/Rigidbody.h"
#include "api/Scene.h"
#include "api/AudioSource.h"
#include <concepts>
#include <iostream>
#include "CoinScript.h"
#include "../Config.h"

using namespace crepe;
using namespace std;

int CoinSubScene::create(Scene & scn){
	vec2 size = {20, 20};

	static int coin_counter = 0;
	string unique_name = "coin_" + to_string(coin_counter++);
	cout << "new coin: "<< unique_name << endl;

	GameObject coin = scn.new_object(unique_name.c_str(),"coin",vec2{650,0},0,1);
	coin.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.kinematic_collision = false,
		.collision_layers = {COLL_LAY_PLAYER},
	});
	coin.add_component<CircleCollider>(size.x / 2).active = false;
	crepe::OptionalRef<crepe::Sprite> coin_sprite = coin.add_component<Sprite>(Asset{"asset/coin/coin1_TVOS.png"}, Sprite::Data{
																   .sorting_in_layer = 100,
																	 .order_in_layer = 100,
																   .size = size,
															   });
	coin_sprite->active = false;
	coin.add_component<Animator>(coin_sprite, ivec2{32, 32}, uvec2{8, 1},
								 Animator::Data{
									 .fps = 15, 
									 .looping = true,
								 }); 
	coin.add_component<AudioSource>(Asset{"asset/sfx/coin_pickup_1.ogg"});
	coin.add_component<BehaviorScript>().set_script<CoinScript>();
	return coin_counter;
}
