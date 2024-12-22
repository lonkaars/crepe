#include "Config.h"
#include "PlayerObject.h"
#include "PlayerScript.h"

using namespace crepe;

PlayerObject::PlayerObject(crepe::GameObject && base)
	: GameObject(std::move(base)),
	  sprite {
		  .body = add_component<Sprite>(
			  Asset {"asset/barry/defaultBody.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_PLAYER,
				  .order_in_layer = 0,
				  .size = vec2(0, 50),
			  }
		  ),
		  .head = add_component<Sprite>(
			  Asset {"asset/barry/defaultHead.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_PLAYER,
				  .order_in_layer = 1,
				  .size = vec2(0, 50),
				  .position_offset = vec2(0, -20),
			  }
		  ),
		  .jetpack = add_component<Sprite>(
			  Asset {"asset/barry/jetpackDefault.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_PLAYER,
				  .order_in_layer = 2,
				  .size = vec2(0, 60),
				  .position_offset = vec2(-20, 0),
			  }
		  )
	  },
	  animator {
		  .body = add_component<Animator>(
			  sprite.body, ivec2(32, 32), uvec2(4, 8),
			  Animator::Data {
				  .fps = 5,
				  .looping = true,
			  }
		  ),
		  .head = add_component<Animator>(
			  sprite.head, ivec2(32, 32), uvec2(4, 8),
			  Animator::Data {
				  .fps = 5,
				  .looping = true,
			  }
		  ),
		  .jetpack = add_component<Animator>(
			  sprite.jetpack, ivec2(32, 44), uvec2(4, 4),
			  Animator::Data {
				  .fps = 5,
				  .looping = true,
			  }
		  ),
	  },
	  body(add_component<Rigidbody>(Rigidbody::Data {
		  .gravity_scale = 20,
		  .body_type = Rigidbody::BodyType::DYNAMIC,
		  .linear_velocity = vec2(100, 0),
		  .collision_layers = {COLL_LAY_BOT_TOP},
		  .collision_layer = COLL_LAY_PLAYER,
	  })),
	  collider(add_component<BoxCollider>(vec2(50, 50))),
	  controller(add_component<BehaviorScript>().set_script<PlayerScript>(*this)) {
	sprite.jetpack.active = false;
	controller.active = false;
}

