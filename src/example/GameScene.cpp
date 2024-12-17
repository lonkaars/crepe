#include "GameScene.h"
#include "Background.h"
#include "Player.h"

#include <cmath>
#include <crepe/api/Animator.h>
#include <crepe/api/Asset.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>
#include <iostream>

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
			return true;
		} else if (event.key == Keycode::LEFT) {
			Transform & cam = this->get_components_by_name<Transform>("camera").front();
			cam.position.x -= 100;
			return true;
		}
		return false;
	}
};

class StartGameScript : public Script {
public:
	void update() {
		Transform & player_transform
			= this->get_components_by_name<Transform>("player").front();

		// Create hole in wall and activate panic lamp
		if (player_transform.position.x > 75 && !this->created_hole) {
			Sprite & lamp_sprite = this->get_components_by_name<Sprite>("start_end").back();
			lamp_sprite.active = true;
			Sprite & hole_sprite = this->get_components_by_name<Sprite>("start_hole").front();
			hole_sprite.active = true;

			RefVector<Rigidbody> frags_rg
				= this->get_components_by_tag<Rigidbody>("wall_fragment");
			RefVector<Sprite> frags_sprite
				= this->get_components_by_tag<Sprite>("wall_fragment");
			for (Rigidbody & frag_rg : frags_rg) {
				frag_rg.active = true;
			}
			for (Sprite & frag_sprite : frags_sprite) {
				frag_sprite.active = true;
			}

			this->created_hole = true;
		}

		// Take jetpack from jetpack stand
		if (player_transform.position.x > 275 && !this->took_jetpack) {
			Animator & jetpack_stand_anim
				= this->get_components_by_name<Animator>("start_begin").back();
			jetpack_stand_anim.next_anim();
			Sprite & jetpack_sprite = this->get_components_by_name<Sprite>("player").back();
			jetpack_sprite.active = true;

			this->took_jetpack = true;
		}

		// Start camera movement, enable player jumping and disable this script
		if (player_transform.position.x > 500) {
			Rigidbody & rb = this->get_components_by_name<Rigidbody>("camera").front();
			rb.data.linear_velocity = vec2(100, 0);
			BehaviorScript & player_script
				= this->get_components_by_name<BehaviorScript>("player").front();
			player_script.active = true;
			BehaviorScript & this_script
				= this->get_components_by_name<BehaviorScript>("start_game_script").front();
			this_script.active = false;
		}
	}

private:
	bool created_hole = false;
	bool took_jetpack = false;
};

void GameScene::load_scene() {
	Background background(*this);

	GameObject camera = new_object("camera", "camera", vec2(650, 0));
	camera.add_component<Camera>(ivec2(990, 720), vec2(1100, 800),
								 Camera::Data{
									 .bg_color = Color::RED,
								 });
	camera.add_component<BehaviorScript>().set_script<MoveCameraScript>();
	camera.add_component<Rigidbody>(Rigidbody::Data{});

	Player player(*this);

	GameObject floor = new_object("floor", "game_world", vec2(0, 325));
	floor.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::STATIC,
	});
	floor.add_component<BoxCollider>(vec2(INFINITY, 200));
	GameObject ceiling = new_object("ceiling", "game_world", vec2(0, -325));
	ceiling.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::STATIC,
	});
	ceiling.add_component<BoxCollider>(vec2(INFINITY, 200));

	GameObject start_game_script = new_object("start_game_script", "script", vec2(0, 0));
	start_game_script.add_component<BehaviorScript>().set_script<StartGameScript>();
}

string GameScene::get_name() const { return "scene1"; }
