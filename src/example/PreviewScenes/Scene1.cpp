

#include "Scene1.h"
#include "api/Animator.h"
#include "api/AudioSource.h"

#include <crepe/api/Asset.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/types.h>

using namespace crepe;

class NextScene : public Script {
	bool key_pressed(const KeyPressEvent & ev) {
		switch (ev.key) {
			case Keycode::ENTER:
				this->set_next_scene("Scene1");
				break;
			default:
				break;
		}
		return false;
	}

	void init() {
		subscribe<KeyPressEvent>(
			[this](const KeyPressEvent & ev) -> bool { return this->key_pressed(ev); });
	}

	void update() {}
};

void Scene1::load_scene() {
	Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;

	GameObject cam = mgr.new_object("camera");
	GameObject background = mgr.new_object("background");
	GameObject player = mgr.new_object("player");
	cam.add_component<Camera>(ivec2{1700, 720}, vec2{2000, 800},
							  Camera::Data{
								  .bg_color = Color::RED,
							  });

	Asset bg_audio{"assets/BGM/Music_Level.mp3"};
	Asset start_begin_asset{"assets/Levels/Title/titleFG_1_TVOS.png"};
	Asset start_middle_asset{"assets/Levels/Title/titleFG_2_TVOS.png"};
	Asset hallway_begin_asset{"assets/Levels/Hallway1/hallway1FG_1_TVOS.png"};
	Asset hallway_middle_asset{"assets/Levels/Hallway1/hallway1FG_2_TVOS.png"};
	Asset player_body{"assets/Characters/Barry/defaultBody.png"};
	Asset player_head{"assets/Characters/Barry/defaultHead.png"};

	cam.add_component<AudioSource>(bg_audio);

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

	auto & player_head_sprite
		= player.add_component<Sprite>(player_head, Sprite::Data{
														.sorting_in_layer = 1,
														.size = vec2{0, 100},
													});
	auto & player_head_anim = player.add_component<Animator>(player_head_sprite, ivec2{32, 32},
															 uvec2{4, 8}, Animator::Data{});
	player_head_anim.loop();

	auto & player_body_sprite
		= player.add_component<Sprite>(player_body, Sprite::Data{
														.sorting_in_layer = 1,
														.size = vec2{0, 100},
														.position_offset = vec2{0,40},
													});
	auto & player_body_anim = player.add_component<Animator>(player_body_sprite, ivec2{32, 32},
															 uvec2{4, 8}, Animator::Data{});
	player_body_anim.loop();
}
