
#include "Coin.h"
#include "api/Asset.h"
#include "api/AudioSource.h"
#include "example/PreviewScenes/Scene1.h"
#include "types.h"

#include <crepe/api/Animator.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

Coin::Coin(Scene1 & s, const vec2 & start_pos) : scene(s) {
	Asset coin_ss{"assets/Entities/coin1_TVOS.png"};
	Asset coin_pickup_audio{"assets/SFX/Obstacle/Coin/coin_pickup_1.mp3"};

	vec2 size = {20, 20};
	GameObject coin = this->scene.create_object("coin", "coin", start_pos, 0, 1);
	this->coin_sprite = coin.add_component<Sprite>(coin_ss, Sprite::Data{
																 .size = size,
															 });

	coin.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 10,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.collision_layers = {0},
	});

	coin.add_component<CircleCollider>(size.x / 2);
	coin.add_component<Animator>(coin_sprite, ivec2{32, 32}, uvec2{8, 1},
								 Animator::Data{
									 .looping = true,
								 });
	this->coin_pickup_audio = coin.add_component<AudioSource>(coin_pickup_audio);
}
	
void Coin::pickup(){
	this->coin_sprite->active = false;
	this->coin_pickup_audio->play();
}
