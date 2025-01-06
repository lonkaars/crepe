#include "PreviewScene.h"

#include "Config.h"
#include "background/BackgroundSubScene.h"

#include <cmath>
#include <crepe/api/Animator.h>
#include <crepe/api/Asset.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/api/AudioSource.h>

#include <crepe/manager/SaveManager.h>
#include <crepe/ValueBroker.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void PreviewScene::load_scene() {
	SaveManager & savemgr = this->get_save_manager();

	GameObject cam = this->new_object("camera");
	GameObject world = this->new_object("world", "TAG", vec2 {0, 0}, 0, 1);
	GameObject missle = this->new_object("missle", "TAG", vec2 {0, 0}, 0, 1);
	GameObject smoke = this->new_object("smoke_particle", "TAG", vec2 {-500, -210}, 0, 1);

	// audio
	Asset bg_audio {"assets/BGM/Music_Level.mp3"};

	Asset start_begin_asset {"assets/Levels/Title/titleFG_1_TVOS.png"};
	Asset start_middle_asset {"assets/Levels/Title/titleFG_2_TVOS.png"};
	Asset hallway_begin_asset {"assets/Levels/Hallway1/hallway1FG_1_TVOS.png"};
	Asset hallway_middle_asset {"assets/Levels/Hallway1/hallway1FG_2_TVOS.png"};
	Asset missle_ss {"assets/Obstacles/Missile/missile.png"};
	Asset smoke_ss {"assets/particles/smoke.png"};

	cam.add_component<Camera>(ivec2 {1700, 720}, vec2 {2000, 800}, Camera::Data {});
	auto & bg_music = background.add_component<AudioSource>(bg_audio);

	bg_music.play_on_awake = true;

	bg_music.volume = 0.5f;

	world.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::STATIC,
		.collision_layers = {0},
	});

	//bottom
	world.add_component<BoxCollider>(vec2 {2000, 800}, vec2 {0, 600});

	auto & npc_body_sprite = npc.add_component<Sprite>(
		npc_body,
		Sprite::Data {
			.sorting_in_layer = 1,
			.order_in_layer = 0,
			.size = {0, 100},
			.position_offset = {0, 40},
		}
	);
	auto & npc_head_sprite = npc.add_component<Sprite>(
		npc_head,
		Sprite::Data {
			.sorting_in_layer = 1,
			.order_in_layer = 0,
			.size = {0, 100},
		}
	);

	npc.add_component<Animator>(
		npc_body_sprite, ivec2 {32, 32}, uvec2 {4, 8},
		Animator::Data {
			.looping = true,
		}
	);
	npc.add_component<Animator>(
		npc_head_sprite, ivec2 {32, 32}, uvec2 {4, 8},
		Animator::Data {
			.looping = true,
		}
	);
	npc.add_component<BoxCollider>(vec2 {50, 100});

	npc.add_component<Rigidbody>(Rigidbody::Data {
		.mass = 1,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = {-50, 0},
		.max_linear_velocity = 40,
		.constraints = {0, 0, 0},
		.elastisity_coefficient = 0,
		.offset = {0, 0},
		.collision_layers = {0},
	});
	npc.add_component<BehaviorScript>().set_script<NpcScript>();

	missle.add_component<BehaviorScript>().set_script<MissleScript>();
	auto & missle_sprite = missle.add_component<Sprite>(
		missle_ss,
		Sprite::Data {
			.order_in_layer = 5,
			.size = {0, 50},
		}
	);
	missle.add_component<Animator>(
		missle_sprite, ivec2 {32, 32}, uvec2 {4, 1},
		Animator::Data {
			.looping = true,
		}
	);
	missle.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.max_linear_velocity = 40,
	});

	auto & missle_ai = missle.add_component<AI>(1000);

	auto & smoke_sprite = smoke.add_component<Sprite>(
		smoke_ss,
		Sprite::Data {
			.sorting_in_layer = 10,
			.order_in_layer = 10,
			.size = {0, 30},
		}
	);

	smoke.add_component<ParticleEmitter>(
		smoke_sprite,
		ParticleEmitter::Data {
			.offset = {0, -60},
			.max_particles = 10,
			.emission_rate = 25,
			.min_angle = 60,
			.max_angle = 120,
			.begin_lifespan = 1,
			.end_lifespan = 2,
		}
	);

	for (int i = 0; i < 200; ++i) {
		int row = i / 10;
		int col = i % 10;
		float x = col * 25 + i;
		float y = row * 25 - 400;
		GameObject game_coin = this->new_object("coin", "coin", vec2 {x, y}, 0, 1);
		Coin coin(game_coin, vec2 {0, 0});
	}
}

void PreviewScene::load_scene() {
	BackgroundSubScene background(*this);

	GameObject camera = new_object("camera", "camera", vec2(650, 0));
	camera.add_component<Camera>(
		ivec2(990, 720), vec2(VIEWPORT_X, VIEWPORT_Y),
		Camera::Data {
			.bg_color = Color::RED,
		}
	);
	camera.add_component<BehaviorScript>().set_script<MoveCameraManualyScript>();
	camera.add_component<Rigidbody>(Rigidbody::Data {});

	PlayerSubScene player(*this);

	GameObject floor = new_object("floor", "game_world", vec2(0, 325));
	floor.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::STATIC,
		.collision_layer = COLL_LAY_BOT_TOP,
	});
	floor.add_component<BoxCollider>(vec2(INFINITY, 200));
	GameObject floor_low = new_object("floor_low", "game_world", vec2(0, 350));
	floor_low.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::STATIC,
		.collision_layer = COLL_LAY_BOT_LOW,
	});
	floor_low.add_component<BoxCollider>(vec2(INFINITY, 200));
	GameObject floor_high = new_object("floor_high", "game_world", vec2(0, 300));
	floor_high.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::STATIC,
		.collision_layer = COLL_LAY_BOT_HIGH,
	});
	GameObject ceiling = new_object("ceiling", "game_world", vec2(0, -325));
	ceiling.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::STATIC,
		.collision_layer = COLL_LAY_BOT_TOP,
	});
	ceiling.add_component<BoxCollider>(vec2(INFINITY, 200));
}

string PreviewScene::get_name() const { return "preview scene"; }
