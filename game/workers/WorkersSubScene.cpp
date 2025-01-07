#include "WorkersSubScene.h"
#include "PanicFromPlayer.h"
#include "WorkerScript.h"

#include "../Config.h"
#include "api/GameObject.h"

#include <crepe/api/Animator.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

WorkersSubScene::WorkersSubScene(Scene & scn) {
	this->worker1(scn, 1200, -50);
	this->worker2(scn, 1300, 20);
	this->worker3(scn, 1400, -40);
	this->worker4(scn, 7250, 50);
	this->worker5(scn, 3400, -20);
	this->worker6(scn, 2000, 30);
	this->worker7(scn, 3725, 35);
	this->worker8(scn, 2200, -15);

	GameObject script = scn.new_object("workers_script");
	script.add_component<BehaviorScript>().set_script<WorkerScript>();
}

void WorkersSubScene::worker1(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_1 = scn.new_object("worker_1", "worker", vec2(start_x, 200));
	Sprite & worker_1_body_sprite = worker_1.add_component<Sprite>(
		Asset {"asset/workers/worker1Body.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 0,
			.size = vec2(0, 50),
		}
	);
	worker_1.add_component<Animator>(
		worker_1_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_1_head_sprite = worker_1.add_component<Sprite>(
		Asset {"asset/workers/worker1Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 1,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_1.add_component<Animator>(
		worker_1_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_1.add_component<BoxCollider>(vec2(50, 50));
	worker_1.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_TOP},
	});
	worker_1.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_1_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_1_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}

void WorkersSubScene::worker2(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_2 = scn.new_object("worker_2", "worker", vec2(start_x, 200));
	Sprite & worker_2_body_sprite = worker_2.add_component<Sprite>(
		Asset {"asset/workers/worker2Body.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 2,
			.size = vec2(0, 50),
		}
	);
	worker_2.add_component<Animator>(
		worker_2_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_2_head_sprite = worker_2.add_component<Sprite>(
		Asset {"asset/workers/worker1Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 3,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_2.add_component<Animator>(
		worker_2_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_2.add_component<BoxCollider>(vec2(50, 50));
	worker_2.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_TOP},
	});
	worker_2.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_2_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_2_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}

void WorkersSubScene::worker3(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_3 = scn.new_object("worker_3", "worker", vec2(start_x, 200));
	Sprite & worker_3_body_sprite = worker_3.add_component<Sprite>(
		Asset {"asset/workers/worker1Body.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 4,
			.size = vec2(0, 50),
		}
	);
	worker_3.add_component<Animator>(
		worker_3_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_3_head_sprite = worker_3.add_component<Sprite>(
		Asset {"asset/workers/worker2Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 5,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_3.add_component<Animator>(
		worker_3_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_3.add_component<BoxCollider>(vec2(50, 50));
	worker_3.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_TOP},
	});
	worker_3.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_3_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_3_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}

void WorkersSubScene::worker4(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_4 = scn.new_object("worker_4", "worker", vec2(start_x, 200));
	Sprite & worker_4_body_sprite = worker_4.add_component<Sprite>(
		Asset {"asset/workers/worker2Body.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 6,
			.size = vec2(0, 50),
		}
	);
	worker_4.add_component<Animator>(
		worker_4_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_4_head_sprite = worker_4.add_component<Sprite>(
		Asset {"asset/workers/worker2Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 7,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_4.add_component<Animator>(
		worker_4_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_4.add_component<BoxCollider>(vec2(50, 50));
	worker_4.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_HIGH},
	});
	worker_4.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_4_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_4_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}

void WorkersSubScene::worker5(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_5 = scn.new_object("worker_5", "worker", vec2(start_x, 200));
	Sprite & worker_5_body_sprite = worker_5.add_component<Sprite>(
		Asset {"asset/workers/workerFatBody.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 8,
			.size = vec2(0, 50),
		}
	);
	worker_5.add_component<Animator>(
		worker_5_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_5_head_sprite = worker_5.add_component<Sprite>(
		Asset {"asset/workers/worker1Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 9,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_5.add_component<Animator>(
		worker_5_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_5.add_component<BoxCollider>(vec2(50, 50));
	worker_5.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_HIGH},
	});
	worker_5.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_5_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_5_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}

void WorkersSubScene::worker6(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_6 = scn.new_object("worker_6", "worker", vec2(start_x, 200));
	Sprite & worker_6_body_sprite = worker_6.add_component<Sprite>(
		Asset {"asset/workers/workerFatBody.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 10,
			.size = vec2(0, 50),
		}
	);
	worker_6.add_component<Animator>(
		worker_6_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_6_head_sprite = worker_6.add_component<Sprite>(
		Asset {"asset/workers/worker2Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 11,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_6.add_component<Animator>(
		worker_6_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_6.add_component<BoxCollider>(vec2(50, 50));
	worker_6.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_LOW},
	});
	worker_6.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_6_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_6_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}

void WorkersSubScene::worker7(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_7 = scn.new_object("worker_7", "worker", vec2(start_x, 200));
	Sprite & worker_7_body_sprite = worker_7.add_component<Sprite>(
		Asset {"asset/workers/workerTallBody.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 12,
			.size = vec2(0, 50),
		}
	);
	worker_7.add_component<Animator>(
		worker_7_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_7_head_sprite = worker_7.add_component<Sprite>(
		Asset {"asset/workers/worker1Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 13,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_7.add_component<Animator>(
		worker_7_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_7.add_component<BoxCollider>(vec2(50, 50));
	worker_7.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_LOW},
	});
	worker_7.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_7_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_7_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}

void WorkersSubScene::worker8(crepe::Scene & scn, float start_x, float init_speed) {
	GameObject worker_8 = scn.new_object("worker_8", "worker", vec2(start_x, 200));
	Sprite & worker_8_body_sprite = worker_8.add_component<Sprite>(
		Asset {"asset/workers/workerTallBody.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 14,
			.size = vec2(0, 50),
		}
	);
	worker_8.add_component<Animator>(
		worker_8_body_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	Sprite & worker_8_head_sprite = worker_8.add_component<Sprite>(
		Asset {"asset/workers/worker2Head.png"},
		Sprite::Data {
			.sorting_in_layer = SORT_IN_LAY_WORKERS,
			.order_in_layer = 15,
			.size = vec2(0, 50),
			.position_offset = vec2(0, -20),
		}
	);
	worker_8.add_component<Animator>(
		worker_8_head_sprite, ivec2(32, 32), uvec2(4, 8),
		Animator::Data {
			.fps = static_cast<unsigned int>(abs(init_speed) / 5),
			.looping = true,
		}
	);
	worker_8.add_component<BoxCollider>(vec2(50, 50));
	worker_8.add_component<Rigidbody>(Rigidbody::Data {
		.gravity_scale = 20,
		.body_type = Rigidbody::BodyType::DYNAMIC,
		.linear_velocity = vec2(init_speed, 0),
		.collision_layers = {COLL_LAY_BOT_LOW},
	});
	worker_8.add_component<BehaviorScript>().set_script<PanicFromPlayer>();

	if (init_speed < 0) {
		worker_8_body_sprite.data.flip = Sprite::FlipSettings {true, false};
		worker_8_head_sprite.data.flip = Sprite::FlipSettings {true, false};
	}
}
