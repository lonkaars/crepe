#include "GameScene.h"
#include "Config.h"
#include "MoveCameraManualyScript.h"
#include "StartGameScript.h"

#include "background/BackgroundSubScene.h"
#include "player/PlayerSubScene.h"

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
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void GameScene::load_scene() {
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

	GameObject start_game_script = new_object("start_game_script", "script", vec2(0, 0));
	start_game_script.add_component<BehaviorScript>().set_script<StartGameScript>();
}

string GameScene::get_name() const { return "scene1"; }
