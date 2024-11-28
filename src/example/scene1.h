#pragma once
#include <memory>
#include <string>

#include <crepe/api/Scene.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/SceneManager.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Rigidbody.h>

#include "playerScript.h"
using namespace crepe;
using namespace std;
class Scene1 : public Scene {
public:
	void load_scene() {
		ComponentManager & mgr = this->component_manager;
		GameObject player = mgr.new_object("player", "tag_scene_1", vec2{0, 0}, 0, 1);
		auto & sprite1
			= player.add_component<Sprite>(make_shared<Texture>("asset/spritesheet/barry_sprite.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		auto& animator1 = player.add_component<Animator>(sprite1,4,1,1);
		auto& rigidbody1 = player.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 10,
			.gravity_scale = 1,
			.use_gravity = true,
		});
		BehaviorScript & behavior_script = player.add_component<BehaviorScript>();
		behavior_script.set_script<PlayerScript>();
		GameObject object2 = mgr.new_object("camera", "tag_scene_1", vec2{1, 0}, 0, 1);
		auto& camera1 = object2.add_component<Camera>(Color(0, 0, 0, 0));
		camera1.
		GameObject object3 = mgr.new_object("scene_1", "tag_scene_1", vec2{2, 0}, 0, 1);
	}

	string get_name() const { return "scene1"; }
};
