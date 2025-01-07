#include "GameScene.h"
#include "Config.h"
#include "MoveCameraManualyScript.h"
#include "StartGameScript.h"
#include "coins/CoinSubScene.h"
#include "coins/CoinPool.h"
#include "coins/CoinSystemScript.h"

#include "background/BackgroundSubScene.h"
#include "hud/HudScript.h"
#include "hud/HudSubScene.h"
#include "hud/SpeedScript.h"
#include "menus/endgame/EndGameSubScene.h"
#include "menus/endgame/EndGameSubScript.h"
#include "player/PlayerSubScene.h"
#include "prefab/ZapperPoolSubScene.h"
#include "workers/WorkersSubScene.h"

#include <cmath>
#include <crepe/api/Animator.h>
#include <crepe/api/Asset.h>
#include <crepe/api/AudioSource.h>
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
	logf(Log::DEBUG, "Loading (main) GameScene...");

	BackgroundSubScene background(*this);

	GameObject camera = new_object(CAMERA_NAME, "camera", vec2(650, 0));
	camera.add_component<Camera>(
		ivec2(990, 720), vec2(VIEWPORT_X, VIEWPORT_Y),
		Camera::Data {
			.bg_color = Color::RED,
		}
	);
	camera.add_component<BehaviorScript>().set_script<MoveCameraManualyScript>();
	camera.add_component<BehaviorScript>().set_script<CoinSystemScript>();
	camera.add_component<BehaviorScript>().set_script<HudScript>();
	camera.add_component<BehaviorScript>().set_script<SpeedScript>();
	
	camera.add_component<Rigidbody>(Rigidbody::Data{});

	PlayerSubScene player(*this);

	WorkersSubScene workers(*this);

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

	ZapperPoolSubScene {*this};

	GameObject start_game_script = new_object("start_game_script", "script", vec2(0, 0));
	start_game_script.add_component<BehaviorScript>().set_script<StartGameScript>();

	//create coin pool
	CoinPool coin_system;
	coin_system.create_coins(*this);

	HudSubScene hud;
	hud.create(*this);

	GameObject background_music = new_object("background_music", "audio", vec2(0, 0));
	Asset background_music_asset {"asset/music/level.ogg"};
	background_music.add_component<AudioSource>(background_music_asset);

	GameObject boom_audio = new_object("boom_audio", "audio", vec2(0, 0));
	Asset boom_audio_asset {"asset/sfx/window_smash.ogg"};
	boom_audio.add_component<AudioSource>(boom_audio_asset);

	GameObject laser = new_object("laser", "laser", vec2(2000, 0));
	Asset laser_asset {"asset/obstacles/laser/laserPower.png"};
	Sprite & laser_sprite = laser.add_component<Sprite>(
		laser_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.order_in_layer = 0,
			.size = vec2(100, 100),
		}
	);
	laser.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.kinematic_collision = false,
		.collision_layer = COLL_LAY_LASER,
	});
	laser.add_component<BoxCollider>(vec2(100, 100));
	GameObject missile = new_object("missile", "missile", vec2(4000, 0));
	Asset missile_asset {"asset/obstacles/missile/missile.png"};
	Sprite & missile_sprite = missile.add_component<Sprite>(
		missile_asset,
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_OBSTACLES,
			.order_in_layer = 0,
			.size = vec2(100, 100),
		}
	);
	missile.add_component<Rigidbody>(Rigidbody::Data {
		.body_type = Rigidbody::BodyType::KINEMATIC,
		.kinematic_collision = false,
		.collision_layer = COLL_LAY_MISSILE,
	});
	missile.add_component<BoxCollider>(vec2(100, 100));

	EndGameSubScene endgamewindow;
	endgamewindow.create(*this);
}

string GameScene::get_name() const { return "scene1"; }
