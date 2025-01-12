
#include "PrevPlayerSubScene.h"

#include "../Config.h"
#include "PrevPlayerScript.h"

#include <crepe/api/Animator.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

#include <crepe/ValueBroker.h>
#include <crepe/manager/SaveManager.h>

using namespace crepe;

PrevPlayerSubScene::PrevPlayerSubScene(Scene & scn) {

	GameObject player = scn.new_object("player", "player", vec2 {800, -100}, 0, 1);
	Asset player_body_asset {"asset/barry/defaultBody.png"};
	Sprite & player_body_sprite = player.add_component<Sprite>(
		player_body_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 0,
			.size = vec2(0, 50),
		}
	);
	player.add_component<Animator>(
		player_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	Asset player_head_asset {"asset/barry/defaultHead.png"};
	Sprite & player_head_sprite = player.add_component<Sprite>(
		player_head_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 1,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	player.add_component<Animator>(
		player_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	Asset player_jetpack_asset {"asset/barry/jetpackDefault.png"};
	Sprite & player_jetpack_sprite = player.add_component<Sprite>(
		player_jetpack_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_PLAYER,
			.order_in_layer = 2,
			.size = vec2(0, 60),
			.position_offset = vec2(-20, 0),
		}
	);
	player_jetpack_sprite.active = false;
	player.add_component<Animator>(
		player_jetpack_sprite, ivec2(32, 44), uvec2(4, 4),
		Animator::Data {
			.fps = 5,
			.looping = true,
		}
	);
	player.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(100, 0),
		.collision_layers = {COLL_LAY_BOT_TOP, 100},
		.collision_layer = COLL_LAY_PLAYER,
	});
	player.add_component<BoxCollider>(vec2(40, 50));
	player.add_component<BehaviorScript>().set_script<PrevPlayerScript>();

	GameObject music = scn.new_object("background_music", "background_music");
	AudioSource & audio = music.add_component<AudioSource>(Asset {"asset/music/level.ogg"});
	audio.loop = true;
	audio.play_on_awake = true;
	audio.active = false;
}
