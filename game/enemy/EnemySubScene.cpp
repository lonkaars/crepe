#include <string>

#include "EnemySubScene.h"
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Sprite.h>
using namespace crepe;
using namespace std;
int EnemySubScene::create(Scene & scn){
	vec2 size = {20, 20};

	static int coin_counter = 0;
	string unique_name = "enemy_" + to_string(coin_counter++);
	GameObject enemy = scn.new_object(unique_name.c_str(),"enemy",vec2{650,0},0,1);
	enemy.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::DYNAMIC,
	});
	crepe::OptionalRef<Sprite> enemy_sprite = enemy.add_component<Sprite>(Asset{"asset/coin/coin1_TVOS.png"}, Sprite::Data{
																   	.sorting_in_layer = 100,
																	.order_in_layer = 100,
																   	.size = vec2(0, 50),
															   });
	enemy.add_component<>
	
	return coin_counter;
}
