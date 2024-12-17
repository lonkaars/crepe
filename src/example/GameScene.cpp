#include "GameScene.h"
#include "Background.h"
#include "api/Animator.h"
#include "api/Asset.h"
#include "api/BoxCollider.h"
#include "api/Transform.h"

#include <cmath>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

class MoveCameraScript : public Script {
public:
	void init() {
		subscribe<KeyPressEvent>(
			[this](const KeyPressEvent & ev) -> bool { return this->keypressed(ev); });
	}

private:
	bool keypressed(const KeyPressEvent & event) {
		if (event.key == Keycode::RIGHT) {
			Transform & cam = this->get_components_by_name<Transform>("camera").front();
			cam.position.x += 100;
		} else if (event.key == Keycode::LEFT) {
			Transform & cam = this->get_components_by_name<Transform>("camera").front();
			cam.position.x -= 100;
		}
		return true;
	}
};

class StartGame : public Script {
public:
	void update() {
		Transform & player_transform
			= this->get_components_by_name<Transform>("player").front();

		// Create hole in wall and activate panic lamp
		if (player_transform.position.x == -310) {
			Sprite & lamp_sprite = this->get_components_by_name<Sprite>("start_end").back();
			lamp_sprite.active = true;
			Sprite & hole_sprite = this->get_components_by_name<Sprite>("start_hole").front();
			hole_sprite.active = true;
		}

		// Take jetpack from jetpack stand
		if (player_transform.position.x == -100) {
			Animator & jetpack_stand_anim
				= this->get_components_by_name<Animator>("start_begin").back();
			jetpack_stand_anim.next_anim();
			Sprite & jetpack_sprite = this->get_components_by_name<Sprite>("player").back();
			jetpack_sprite.active = true;
		}

		// Start camera movement
		if (player_transform.position.x == 150) {
			Rigidbody & rb = this->get_components_by_name<Rigidbody>("camera").front();
			rb.data.linear_velocity = vec2(100, 0);
		}
	}
};

void GameScene::load_scene() {
	Background background(*this);

	GameObject camera = new_object("camera", "camera", vec2(250, 0));
	camera.add_component<Camera>(ivec2(990, 720), vec2(1100, 800),
								 Camera::Data{
									 .bg_color = Color::RED,
								 });
	camera.add_component<BehaviorScript>().set_script<MoveCameraScript>();
	camera.add_component<Rigidbody>(Rigidbody::Data{
		.linear_velocity = vec2(0, 0),
	});

	GameObject player = new_object("player", "player", vec2(-500, 200));
	Asset player_body_asset{"asset/jetpack_joyride/barry/defaultBody.png"};
	Sprite & player_body_sprite
		= player.add_component<Sprite>(player_body_asset, Sprite::Data{
															  .sorting_in_layer = 10,
															  .order_in_layer = 0,
															  .size = vec2(0, 50),
														  });
	player.add_component<Animator>(player_body_sprite, ivec2(32, 32), uvec2(4, 8),
								   Animator::Data{
									   .fps = 5,
									   .looping = true,
								   });
	Asset player_head_asset{"asset/jetpack_joyride/barry/defaultHead.png"};
	Sprite & player_head_sprite
		= player.add_component<Sprite>(player_head_asset, Sprite::Data{
															  .sorting_in_layer = 10,
															  .order_in_layer = 1,
															  .size = vec2(0, 50),
															  .position_offset = vec2(0, -20),
														  });
	player.add_component<Animator>(player_head_sprite, ivec2(32, 32), uvec2(4, 8),
								   Animator::Data{
									   .fps = 5,
									   .looping = true,
								   });
	Asset player_jetpack_asset{"asset/jetpack_joyride/barry/jetpackDefault.png"};
	Sprite & player_jetpack_sprite = player.add_component<Sprite>(
		player_jetpack_asset, Sprite::Data{
								  .sorting_in_layer = 10,
								  .order_in_layer = 2,
								  .size = vec2(0, 60),
								  .position_offset = vec2(-20, 0),
							  });
	player_jetpack_sprite.active = false;
	player.add_component<Animator>(player_jetpack_sprite, ivec2(32, 44), uvec2(4, 4),
								   Animator::Data{
									   .fps = 5,
									   .looping = true,
								   });
	player.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(100, 0),
	});
	player.add_component<BoxCollider>(vec2(50, 50));

	GameObject game_world = new_object("game_world", "game_world", vec2(0, 325));
	game_world.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::STATIC,
	});
	game_world.add_component<BoxCollider>(vec2(INFINITY, 200));

	GameObject start_game_scritp = new_object("start_game_script", "script", vec2(0, 0));
	start_game_scritp.add_component<BehaviorScript>().set_script<StartGame>();
}

string GameScene::get_name() const { return "scene1"; }
