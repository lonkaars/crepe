#include <crepe/api/Transform.h>

#include "Config.h"
#include "ZapperObject.h"

using namespace crepe;

ZapperObject::ZapperObject(crepe::GameObject && base)
	: GameObject(std::move(base)),
	  sprite {
		  .orb_start = add_component<Sprite>(
			  Asset {"asset/obstacles/zapper/orbAnim.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = 1,
				  .size = vec2(0, 42) * SCALE,
			  }
		  ),
		  .orb_end = add_component<Sprite>(
			  sprite.orb_start.source,
			  Sprite::Data {
				  .flip = {true, true},
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = 1,
				  .size = vec2(0, 42) * SCALE,
			  }
		  ),
		  .glow_start = add_component<Sprite>(
			  Asset {"asset/obstacles/zapper/regular_zappers/glow.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = -1,
				  .size = vec2(128, 128) * SCALE,
			  }
		  ),
		  .glow_end = add_component<Sprite>(
			  sprite.glow_start.source,
			  Sprite::Data {
				  .flip = {true, true},
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = -1,
				  .size = vec2(128, 128) * SCALE,
			  }
		  ),
		  .beam = add_component<Sprite>(
			  Asset {"asset/obstacles/zapper/regular_zappers/zapEffect.png"},
			  Sprite::Data {
				  .sorting_in_layer = SORT_IN_LAY_OBSTACLES,
				  .order_in_layer = 0,
				  .size = vec2(0, 40 * SCALE),
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
	  },
	  body {add_component<Rigidbody>(Rigidbody::Data {
		  .body_type = Rigidbody::BodyType::KINEMATIC,
		  .kinematic_collision = false,
		  .collision_layer = COLL_LAY_ZAPPER,
	  })},
	  collider {add_component<BoxCollider>(vec2(0, 0))} {
	this->place(this->transform.position, 0, 300);
	this->set_active(false);
}

void ZapperObject::place(const crepe::vec2 & position, float rotation, float length) {
	this->transform.position = position;
	this->transform.rotation = rotation;

	vec2 offset = vec2(0, 1) * length / 2;

	this->sprite.orb_start.data.position_offset = offset;
	this->sprite.glow_start.data.position_offset = offset;
	this->sprite.orb_end.data.position_offset = -offset;
	this->sprite.glow_end.data.position_offset = -offset;

	this->sprite.beam.data.size.x = length;

	this->collider.dimensions = offset.rotate(rotation) * 2 + vec2(30, 30) * SCALE;
}

void ZapperObject::set_active(bool active) {
	this->sprite.orb_start.active = active;
	this->sprite.orb_end.active = active;
	this->sprite.glow_start.active = active;
	this->sprite.glow_end.active = active;
	this->sprite.beam.active = active;

	this->animator.orb_start.active = active;
	this->animator.orb_end.active = active;
	this->animator.glow_start.active = active;
	this->animator.glow_end.active = active;

	this->body.active = active;
	this->collider.active = active;
}

