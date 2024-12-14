#include "Scene1.h"
#include "ValueBroker.h"
#include "api/CircleCollider.h"

#include <crepe/api/AI.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Asset.h>
#include <crepe/api/AudioSource.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/manager/ResourceManager.hpp>
#include <crepe/manager/SaveManager.h>
#include <crepe/system/CollisionSystem.h>
#include <crepe/types.h>
#include <crepe/util/OptionalRef.h>
#include <iostream>
#include <string>

using namespace crepe;

class CircleScript : public Script{
	bool on_collision(const CollisionEvent & ev){
		auto & coll = ev.info;
		if (coll.other_metadata.tag != "circle") return true;

		//coll.other_transform.position += coll.resolution / 2;
		coll.this_transform.position += coll.resolution / 2;
		coll.this_rigidbody.data.linear_velocity = {0, 0};
		//coll.other_rigidbody.data.linear_velocity = {0, 0};

		return true;
	}
	void init(){
		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->on_collision(ev); });

	}

};

class MissleScript : public Script {

private:
	vec2 mouse_pos;

	bool mouse_click(const MouseClickEvent & ev) {
		this->mouse_pos = {(float) ev.mouse_x, (float) ev.mouse_y};
		this->get_component<Transform>().position = mouse_pos;
		return true;
	}
	void init() {
		subscribe<MouseClickEvent>(
			[this](const MouseClickEvent & ev) -> bool { return this->mouse_click(ev); });
	}
	void update() {
		const auto & player = this->get_components_by_name<Transform>("player").front().get();
		auto & m_ai = this->get_component<AI>();
		const auto & rb = this->get_component<Rigidbody>();
		auto & missle = this->get_component<Sprite>();
		m_ai.seek_target = player.position;
		m_ai.seek_on();

		if (rb.data.linear_velocity.x > 0) {
			missle.data.flip = {true, false};
		} else {
			missle.data.flip = {false, false};
		}
	}
};
class NpcScript : public Script {
	void init() {}
	void update() {
		auto & rb = this->get_component<Rigidbody>();
		auto & npc = this->get_component<Sprite>();
		auto & transform = this->get_component<Transform>();

		if (transform.position.x < -990) {
			rb.data.linear_velocity.x *= -1;
		}
		if (transform.position.x > 990) {
			rb.data.linear_velocity.x *= -1;
		}

		if (rb.data.linear_velocity.x < 0) {
			npc.data.flip = {true, false};
		} else {
			npc.data.flip = {false, false};
		}

		//auto & savemgr = this->get_save_manager();
		//savemgr.set("npc_x", transform.position.x);
		//savemgr.set("npc_y", transform.position.y);
	}
};

class PlayerScript : public Script {
private:
	OptionalRef<Animator> head_anim;
	OptionalRef<Animator> body_anim;
	OptionalRef<Sprite> head;
	OptionalRef<Sprite> body;

private:
	float move_speed = 100;

private:
	bool npc_collision(const CollisionEvent & ev) {
		auto & coll = ev.info;
		if (coll.other_metadata.tag != "npc_tag") return true;

		coll.other_transform.position += coll.resolution / 2;
		coll.this_transform.position += coll.resolution / 2;
		//coll.this_rigidbody.data.linear_velocity = {0, 0};
		//coll.other_rigidbody.data.linear_velocity = {0, 0};

		return true;
	}
	bool key_pressed(const KeyPressEvent & ev) {
		switch (ev.key) {
			case Keycode::A:
				this->get_component<Rigidbody>().data.linear_velocity.x = -move_speed;
				this->body->data.flip = {true, false};
				this->head->data.flip = {true, false};
				break;
			case Keycode::D:
				this->get_component<Rigidbody>().data.linear_velocity.x = move_speed;
				this->body->data.flip = {false, false};
				this->head->data.flip = {false, false};
				break;

			case Keycode::SPACE:
				this->get_component<Rigidbody>().data.linear_velocity.y = -move_speed;
				break;
			case Keycode::D0:
				this->body_anim->set_anim(0);
				this->head_anim->set_anim(0);
				break;
			case Keycode::D1:
				this->body_anim->set_anim(1);
				this->head_anim->set_anim(1);
				break;
			case Keycode::D2:
				this->body_anim->set_anim(2);
				this->head_anim->set_anim(2);
				break;
			case Keycode::D3:
				this->body_anim->set_anim(3);
				this->head_anim->set_anim(3);
				break;
			case Keycode::D4:
				this->body_anim->set_anim(4);
				this->head_anim->set_anim(4);
				break;
			case Keycode::D5:
				this->body_anim->set_anim(5);
				this->head_anim->set_anim(5);
				break;
			case Keycode::D6:
				this->body_anim->set_anim(6);
				this->head_anim->set_anim(6);
				break;
			case Keycode::D7:
				this->body_anim->set_anim(7);
				this->head_anim->set_anim(7);
				break;
			case Keycode::LEFT:
				this->head->data.angle_offset -= 1;
				break;
			case Keycode::RIGHT:
				this->head->data.angle_offset += 1;
				break;
			case Keycode::UP:
				this->head->data.scale_offset += 0.1;
				break;
			case Keycode::DOWN:
				this->head->data.scale_offset -= 0.1;
				break;
			case Keycode::P:
				this->get_component<AudioSource>().play();
				break;
			case Keycode::Q:
				this->get_components_by_name<Camera>("camera").front().get().data.zoom -= 0.01;
				break;
			case Keycode::E:
				this->get_components_by_name<Camera>("camera").front().get().data.zoom += 0.01;
				break;
			case Keycode::J:
				this->get_components_by_name<Camera>("camera")
					.front()
					.get()
					.data.postion_offset.x
					-= move_speed;
				break;
			case Keycode::K:
				this->get_components_by_name<Camera>("camera")
					.front()
					.get()
					.data.postion_offset.y
					-= move_speed;
				break;
			case Keycode::L:
				this->get_components_by_name<Camera>("camera")
					.front()
					.get()
					.data.postion_offset.x
					+= move_speed;
				break;
			case Keycode::I:
				this->get_components_by_name<Camera>("camera")
					.front()
					.get()
					.data.postion_offset.y
					+= move_speed;
				break;
				//todo
			case Keycode::PAGE_UP:
			case Keycode::PAGE_DOWN:
			case Keycode::HOME:
				break;
			default:
				break;
		}
		return false;
	}

	void init() {
		auto animations = this->get_components<Animator>();
		body_anim = animations[0];
		head_anim = animations[1];

		auto sprites = this->get_components<Sprite>();
		body = sprites[0];
		head = sprites[1];

		subscribe<KeyPressEvent>(
			[this](const KeyPressEvent & ev) -> bool { return this->key_pressed(ev); });

		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->npc_collision(ev); });
	};

	void update() {
		//auto & savemgr = this->get_save_manager();
		const auto & pos = this->get_component<Transform>().position;

		//savemgr.set("player_x", pos.x);
		//savemgr.set("player_y", pos.y);
	}
};

void Scene1::load_scene() {
	SaveManager & savemgr = this->get_save_manager();

	ValueBroker player_y = savemgr.get<std::string>("HALLO", "0");
	ValueBroker player_x = savemgr.get<std::string>("JAJKJAKJ", "750");
	ValueBroker npc_x = savemgr.get<std::string>("SDFGHJKL", "-750");
	ValueBroker npc_y = savemgr.get<std::string>("JAKJKAJKj", "0");

	std::cout << player_x.get() << " " << player_y.get() << " " << npc_x.get() << " "
			  << npc_y.get() << std::endl;

	GameObject cam = this->new_object("camera");
	GameObject world = this->new_object("world", "TAG", vec2{0, 0}, 0, 1);
	GameObject background = this->new_object("background");
	GameObject player = this->new_object("player", "TAG", vec2{750, 0}, 0, 1);
	GameObject npc = this->new_object("npc", "npc_tag", vec2{-750, 0}, 0, 1);
	GameObject missle = this->new_object("missle", "TAG", vec2{0, 0}, 0, 1);
	GameObject smoke = this->new_object("smoke_particle", "TAG", vec2{0, 0}, 0, 1);

	// audio
	Asset bg_audio{"assets/BGM/Music_Level.mp3"};
	Asset sfx_audio{"assets/SFX/Barry/Player_bones.mp3"};

	// sprites
	Asset start_begin_asset{"assets/Levels/Title/titleFG_1_TVOS.png"};
	Asset start_middle_asset{"assets/Levels/Title/titleFG_2_TVOS.png"};
	Asset hallway_begin_asset{"assets/Levels/Hallway1/hallway1FG_1_TVOS.png"};
	Asset hallway_middle_asset{"assets/Levels/Hallway1/hallway1FG_2_TVOS.png"};
	Asset player_body{"assets/Characters/Barry/defaultBody.png"};
	Asset player_head{"assets/Characters/Barry/defaultHead.png"};
	Asset npc_body{"assets/workers/worker1Body.png"};
	Asset npc_head{"assets/workers/worker1Head.png"};
	Asset missle_ss{"assets/Obstacles/Missile/missile.png"};
	Asset smoke_ss{"assets/particles/smoke.png"};

	Asset circle_ss{"asset/texture/circle.png"};

	cam.add_component<Camera>(ivec2{1700, 720}, vec2{2000, 800}, Camera::Data{});

	auto & bg_music = background.add_component<AudioSource>(bg_audio);

	bg_music.play_on_awake = true;
	bg_music.volume = 0.5f;

	background.add_component<Sprite>(start_begin_asset, Sprite::Data{
															.order_in_layer = 1,
															.size = vec2{0, 800},
															.position_offset = vec2{-600, 0},
														});

	background.add_component<Sprite>(start_middle_asset, Sprite::Data{
															 .order_in_layer = 2,
															 .size = vec2{0, 800},
														 });

	background.add_component<Sprite>(hallway_begin_asset, Sprite::Data{
															  .order_in_layer = 1,
															  .size = vec2{0, 800},
															  .position_offset = vec2{100, 0},
														  });

	background.add_component<Sprite>(hallway_middle_asset, Sprite::Data{
															   .order_in_layer = 2,
															   .size = vec2{0, 800},
															   .position_offset = vec2{600, 0},
														   });

	world.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::STATIC,
		.collision_layers = {0},
	});

	//bottom
	world.add_component<BoxCollider>(vec2{0, 600}, vec2{2000, 800});

	auto & player_head_sprite
		= player.add_component<Sprite>(player_head, Sprite::Data{
														.sorting_in_layer = 1,
														.order_in_layer = 1,
														.size = vec2{0, 100},
													});
	auto & player_head_anim = player.add_component<Animator>(player_head_sprite, ivec2{32, 32},
															 uvec2{4, 8}, Animator::Data{});
	player_head_anim.loop();

	auto & player_body_sprite
		= player.add_component<Sprite>(player_body, Sprite::Data{
														.sorting_in_layer = 1,
														.order_in_layer = 0,
														.size = vec2{0, 100},
														.position_offset = vec2{0, 40},
													});
	auto & player_body_anim = player.add_component<Animator>(player_body_sprite, ivec2{32, 32},
															 uvec2{4, 8}, Animator::Data{});
	player_body_anim.loop();

	player.add_component<BehaviorScript>().set_script<PlayerScript>();
	player.add_component<AudioSource>(sfx_audio);
	player.add_component<BoxCollider>(vec2{0, 0}, vec2{50, 100});

	player.add_component<Rigidbody>(Rigidbody::Data{
		.mass = 10,
		.gravity_scale = 1,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = {0, 0},
		.constraints = {0, 0, 0},
		.elastisity_coefficient = 0,
		.offset = {0, 0},
		.collision_layers = {0},
	});

	auto & npc_body_sprite
		= npc.add_component<Sprite>(npc_body, Sprite::Data{
												  .sorting_in_layer = 1,
												  .order_in_layer = 0,
												  .size = {0, 100},
												  .position_offset = {0, 40},
											  });
	auto & npc_head_sprite = npc.add_component<Sprite>(npc_head, Sprite::Data{
																	 .sorting_in_layer = 1,
																	 .order_in_layer = 0,
																	 .size = {0, 100},
																 });

	npc.add_component<Animator>(npc_body_sprite, ivec2{32, 32}, uvec2{4, 8},
								Animator::Data{
									.looping = true,
								});
	npc.add_component<Animator>(npc_head_sprite, ivec2{32, 32}, uvec2{4, 8},
								Animator::Data{
									.looping = true,
								});
	npc.add_component<BoxCollider>(vec2{0, 0}, vec2{50, 100});

	npc.add_component<Rigidbody>(Rigidbody::Data{
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
	auto & missle_sprite = missle.add_component<Sprite>(missle_ss, Sprite::Data{
																	   .order_in_layer = 5,
																	   .size = {0, 50},
																   });
	missle.add_component<Animator>(missle_sprite, ivec2{32, 32}, uvec2{4, 1},
								   Animator::Data{
									   .looping = true,
								   });
	missle.add_component<Rigidbody>(Rigidbody::Data{
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.max_linear_velocity = 40,
	});

	auto & missle_ai = missle.add_component<AI>(1000);

	auto & smoke_sprite = smoke.add_component<Sprite>(smoke_ss, Sprite::Data{
																	.sorting_in_layer = 10,
																	.order_in_layer = 10,
																	.size = {0, 100},
																});

	smoke.add_component<ParticleEmitter>(ParticleEmitter::Data{
		.position = {0, 0},
		.max_particles = 10,
		.emission_rate = 1,
		.min_speed = 6,
		.max_speed = 20,
		.min_angle = -20,
		.max_angle = 20,
		.begin_lifespan = 0,
		.end_lifespan = 60,
		.force_over_time = {0, 0},
		.boundary{
			.width = 1000,
			.height = 1000,
			.offset = {0, 0},
			.reset_on_exit = false,
		},
		.sprite = smoke_sprite,
	});

	for (int i = 0; i < 5; ++i) {
		GameObject circle = this->new_object("circle", "circle", vec2{(float)i, (float)(i * 30)}, 0, 1);
		vec2 size = {20, 20};
		circle.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 10,
			.gravity_scale = 1,
			.body_type = Rigidbody::BodyType::DYNAMIC,
			.collision_layers = {0},
		});
		circle.add_component<CircleCollider>(vec2{0, 0}, size.x / 2);
		circle.add_component<Sprite>(circle_ss, Sprite::Data{
													.sorting_in_layer = 5,
													.order_in_layer = 5,
													.size = size,
												});
		circle.add_component<BehaviorScript>().set_script<CircleScript>();
	}
}
