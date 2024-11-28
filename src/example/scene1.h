#pragma once
#include <memory>
#include <string>
#include <functional>
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
#include <crepe/api/BoxCollider.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Button.h>
#include "playerScript.h"
using namespace crepe;
using namespace std;
class Scene1 : public Scene {
public:
	void load_scene() {
		ComponentManager & mgr = this->component_manager;
		GameObject player = mgr.new_object("player", "tag_scene_1", vec2{300, -200}, 90, 0.5);
		auto & sprite1
			= player.add_component<Sprite>(make_shared<Texture>("asset/spritesheet/barry_sprite.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		auto& animator1 = player.add_component<Animator>(sprite1,1,4,1);
		auto& rigidbody1 = player.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 10,
			.gravity_scale = 0.1,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.linear_damping = vec2{0.96,0.96},
			.angular_velocity = 0,
			
			.angular_damping = 0.99,
			.use_gravity = false,
		});
		auto& particle_sprite = player.add_component<Sprite>(make_shared<Texture>("asset/texture/bullet.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		//jetpack_particles.set_parent(player);
	auto& jetpack_emitter = player.add_component<ParticleEmitter>(ParticleEmitter::Data {
			.position = vec2{20,20},
			.max_particles = 20,
			.emission_rate = 100,
			.min_speed = 20,
			.max_speed = 100,
			.min_angle = 0,
			.max_angle = 20,
			.begin_lifespan = 10.0,
			.end_lifespan = 20.0,
			.force_over_time = vec2{200,200},
			.boundary = ParticleEmitter::Boundary{200,200,vec2{0,0},true},
			.sprite = particle_sprite,
	});	
		player.add_component<BoxCollider>(vec2{0,0},200,200);
		
		BehaviorScript & behavior_script = player.add_component<BehaviorScript>();
		
		
		behavior_script.set_script<PlayerScript>();
		GameObject camera = mgr.new_object("camera", "tag_scene_1", vec2{0, 0}, 0, 1);
		auto& camera1 = camera.add_component<Camera>(Color(0, 0, 0, 0));
		camera1.aspect_width = 10000;
		camera1.aspect_height = 10000;
		camera1.x = 200;
		camera1.y = -200;
		GameObject world = mgr.new_object("world", "tag_scene_1", vec2{2, 0}, 0, 1);
		auto& world_body = world.add_component<Rigidbody>(Rigidbody::Data{
			.body_type = Rigidbody::BodyType::STATIC,
			
		});

		//colliders
		auto& up = world.add_component<BoxCollider>(vec2{400, -200}, 800, 20);
		auto& down = world.add_component<BoxCollider>(vec2{600, 330}, 800, 10);
		auto& left = world.add_component<BoxCollider>(vec2{170, 0}, 10, 800);
		auto& right = world.add_component<BoxCollider>(vec2{860, 0}, 10, 800); 


		GameObject jetpack_particles = mgr.new_object("jetpack particles", "tag_scene_1", vec2{100, 100}, 90, 1);
	// 	auto& particle_sprite = jetpack_particles.add_component<Sprite>(make_shared<Texture>("asset/texture/bullet.png"),
	// 										Color(0, 0, 0, 0), FlipSettings{false, false});
	// 	jetpack_particles.set_parent(player);
	// 	auto& jetpack_emitter = jetpack_particles.add_component<ParticleEmitter>(ParticleEmitter::Data {
	// 		.position = vec2{20,20},
	// 		.max_particles = 20,
	// 		.emission_rate = 100,
	// 		.min_speed = 20,
	// 		.max_speed = 100,
	// 		.min_angle = 0,
	// 		.max_angle = 20,
	// 		.begin_lifespan = 10.0,
	// 		.end_lifespan = 20.0,
	// 		.force_over_time = vec2{200,200},
	// 		.boundary = ParticleEmitter::Boundary{200,200,vec2{0,0},true},
	// 		.sprite = particle_sprite,
	// });
	std::function<void()> on_click = [&]() { std::cout << "button clicked\n"; };
	GameObject button = mgr.new_object("button", "tag_scene_1", vec2{400, 400}, 0, 0.2);
	auto& button_cmp = button.add_component<Button>(100,100,on_click,false);
	auto& button_texture = button.add_component<Sprite>(make_shared<Texture>("asset/texture/bullet.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});



	
		GameObject ball = mgr.new_object("boll", "tag_scene_1", vec2{350, -150}, 0, 0.2);
		auto & ball_sprite
			= ball.add_component<Sprite>(make_shared<Texture>("asset/spritesheet/barry_sprite.png"),
											Color(0, 0, 0, 0), FlipSettings{false, false});
		auto& ball_animator = ball.add_component<Animator>(sprite1,1,4,1);
		auto& ball_rigidbody = ball.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 10,
			.gravity_scale = 0.1,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.linear_velocity = vec2{0.5,0.5},
			.angular_velocity = 10000,
			.use_gravity = false,
			.bounce = true,
			.elastisity = 1.2,
		});
		ball.add_component<BoxCollider>(vec2{0,0},200,200);
	}

	string get_name() const { return "scene1"; }
};
