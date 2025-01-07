#include "CoinSubScene.h"
#include "api/Animator.h"
#include "api/BehaviorScript.h"
#include "api/CircleCollider.h"
#include "api/Rigidbody.h"
#include "api/Scene.h"
#include "api/AudioSource.h"
#include "CoinScript.h"
#include "../Config.h"

using namespace crepe;
using namespace std;

int CoinSubScene::create(Scene & scn,int coin_counter){
	vec2 size = {20, 20};

	string unique_name = "coin_" + to_string(coin_counter++);

	GameObject coin = scn.new_object(unique_name.c_str(),"coin",vec2{650,0},0,1);
	coin.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.kinematic_collision = false,
		.collision_layers = {COLL_LAY_PLAYER},
	});
	coin.add_component<CircleCollider>((size.x / 2)-3).active = false;
	crepe::OptionalRef<crepe::Sprite> coin_sprite = coin.add_component<Sprite>(Asset{"asset/coin/coin1_TVOS.png"}, Sprite::Data{
																   .sorting_in_layer = SORT_IN_LAY_COINS,
																	 .order_in_layer = 0,
																   .size = size,
															   });
	coin_sprite->active = false;
	coin.add_component<Animator>(coin_sprite, ivec2{32, 32}, uvec2{8, 1},
								 Animator::Data{
									 .fps = 15, 
									 .looping = true,
								 }); 
	coin.add_component<AudioSource>(Asset{"asset/sfx/coin_pickup_1.ogg"});
	return coin_counter;
}
