#include "ZapperObject.h"
#include "Config.h"

using namespace crepe;

ZapperObject::ZapperObject(crepe::GameObject && base)
	: GameObject(std::move(base)),
	  sprite {
		  .orb_start = add_component<Sprite>(
			  Asset {"asset/obstacles/zapper/orbAnim.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = 1,
				  .size = vec2 {0, 1} * SCALE,
				  .position_offset = {0, 100},
			  }
		  ),
		  .orb_end = add_component<Sprite>(
			  sprite.orb_start.source,
			  Sprite::Data {
				  .flip = {true, true},
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = 1,
				  .size = vec2 {0, 1} * SCALE,
				  .position_offset = {0, -100},
			  }
		  ),
		  .glow_start = add_component<Sprite>(
			  Asset {"asset/obstacles/zapper/regular_zappers/glow.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = -1,
				  .size = vec2 {2, 2} * SCALE,
				  .position_offset = {0, 100},
			  }
		  ),
		  .glow_end = add_component<Sprite>(
			  sprite.glow_start.source,
			  Sprite::Data {
				  .flip = {true, true},
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = -1,
				  .size = vec2 {2, 2} * SCALE,
				  .position_offset = {0, -100},
			  }
		  ),
		  .beam = add_component<Sprite>(
			  Asset {"asset/obstacles/zapper/regular_zappers/zapEffect.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = 0,
				  .size = vec2 {200, 50},
				  .angle_offset = 90,
			  }
		  ),
	  },
	  animator {
		  .orb_start = add_component<Animator>(
			  sprite.orb_start, ivec2(62, 42), uvec2(4, 1),
			  Animator::Data {
				  .fps = 10,
				  .looping = true,
			  }
		  ),
		  .orb_end = add_component<Animator>(
			  sprite.orb_end, ivec2(62, 42), uvec2(4, 1), animator.orb_start.data
		  ),
		  .glow_start = add_component<Animator>(
			  sprite.glow_start, ivec2(128, 128), uvec2(16, 1),
			  Animator::Data {
				  .fps = 30,
				  .looping = true,
			  }
		  ),
		  .glow_end = add_component<Animator>(
			  sprite.glow_end, ivec2(128, 128), uvec2(16, 1), animator.glow_start.data
		  ),
	  } {}
