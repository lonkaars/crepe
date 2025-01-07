#include "PreviewScene.h"

#include "Config.h"
#include "missile/MissilePool.h"
#include "missile/SpawnEvent.h"
#include "preview/PrevPlayerSubScene.h"
#include "preview/NpcSubScene.h"
#include "background/BackgroundSubScene.h"
#include "preview/SmokeSubScene.h"

#include "missile/MissileSubScene.h"

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
#include <iostream>

using namespace crepe;
using namespace std;

void PreviewScene::load_scene() {

	BackgroundSubScene background(*this);

	GameObject camera = new_object("camera", "camera", vec2(650, 0));
	camera.add_component<Camera>(
		ivec2(990, 720), vec2(VIEWPORT_X, VIEWPORT_Y),
		Camera::Data {
			.bg_color = Color::RED,
		}
	);
	camera.add_component<Rigidbody>(Rigidbody::Data {});
	camera.add_component<BehaviorScript>().set_script<MissileSpawnEventHandler>();

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
	GameObject world = this->new_object("world", "TAG", vec2 {0, 0}, 0, 1);

	world.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::STATIC,
		.collision_layers = {0},
	});

	PrevPlayerSubScene player(*this);
	NpcSubScene npc(*this);
	SmokeSubScene smoke(*this);
	MissilePool mpool(*this);

	/*
	
	for (int i = 0; i < 200; ++i) {
		int row = i / 10;
		int col = i % 10;
		float x = col * 25 + i;
		float y = row * 25 - 400;
		GameObject game_coin = this->new_object("coin", "coin", vec2 {x, y}, 0, 1);
		Coin coin(game_coin, vec2 {0, 0});
	}
	  */
}

string PreviewScene::get_name() const { return "preview scene"; }
