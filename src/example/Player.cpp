#include "Player.h"

#include <crepe/api/Animator.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

class PlayerScript : public Script {
public:
	void update() {
		Rigidbody & rb = this->get_components_by_name<Rigidbody>("player").front();
		if (this->get_key_state(Keycode::SPACE))
			rb.add_force_linear(vec2(0, -10));
	}
};

Player::Player(Scene & scn) {
	GameObject player = scn.new_object("player", "player", vec2(-100, 200));
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
		.gravity_scale = 10,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(100, 0),
	});
	player.add_component<BoxCollider>(vec2(50, 50));
	player.add_component<BehaviorScript>().set_script<PlayerScript>().active = false;
}
