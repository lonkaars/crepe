#include "StartSubScene.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>

using namespace crepe;
using namespace std;

float StartSubScene::create(Scene & scn, float begin_x) {
	this->create_wall_fragments(scn, begin_x - 300);

	GameObject begin = scn.new_object("start_begin", "background", vec2(begin_x, 0));
	Asset begin_asset{"asset/background/start/titleFG_1_TVOS.png"};
	begin.add_component<Sprite>(begin_asset, Sprite::Data{
												 .sorting_in_layer = SORT_IN_LAY_BACKGROUND,
												 .order_in_layer = 0,
												 .size = vec2(0, GAME_HEIGHT),
											 });
	GameObject hole = scn.new_object("start_hole", "background", vec2(begin_x - 250, 140));
	Asset hole_asset{"asset/background/start/titleWallHole.png"};
	Sprite & hole_sprite = hole.add_component<Sprite>(
		hole_asset, Sprite::Data{
						.sorting_in_layer = SORT_IN_LAY_BACKGROUND,
						.order_in_layer = 1,
						.size = vec2(0, 200),
					});
	hole_sprite.active = false;
	begin_x += 700;

	this->add_table(begin, vec2(-150, 150));
	this->add_light(begin, vec2(-125, -150));
	this->add_jetpack_stand(begin, vec2(-125, 200));

	GameObject end = scn.new_object("start_end", "background", vec2(begin_x, 0));
	Asset end_asset{"asset/background/start/titleFG_2_TVOS.png"};
	end.add_component<Sprite>(end_asset, Sprite::Data{
											 .sorting_in_layer = SORT_IN_LAY_BACKGROUND,
											 .order_in_layer = 1,
											 .size = vec2(0, GAME_HEIGHT),
										 });
	begin_x += 100;

	this->add_lamp(end, vec2(-350, -95));

	return begin_x;
}

void StartSubScene::add_lamp(GameObject & obj, vec2 offset, unsigned int fps) {
	Asset lamp_asset{"asset/background/start/alarmLight_TVOS.png"};
	obj.add_component<Sprite>(lamp_asset, Sprite::Data{
											  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
											  .order_in_layer = 0,
											  .size = vec2(0, 100),
											  .position_offset = offset,
										  });
	Asset lamp_glow_asset{"asset/background/start/alarmGlow_TVOS.png"};
	Sprite & lamp_glow_sprite = obj.add_component<Sprite>(
		lamp_glow_asset, Sprite::Data{
							 .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
							 .order_in_layer = 1,
							 .size = vec2(0, 300),
							 .position_offset = offset - vec2(65, -55),
						 });
	lamp_glow_sprite.active = false;
	obj.add_component<Animator>(lamp_glow_sprite, ivec2(422, 384), uvec2(6, 1),
								Animator::Data{
									.fps = fps,
									.looping = true,
								});
}

void StartSubScene::add_table(GameObject & obj, vec2 offset) {
	Asset table_asset{"asset/background/start/table.png"};
	obj.add_component<Sprite>(table_asset, Sprite::Data{
											   .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
											   .order_in_layer = 0,
											   .size = vec2(0, 100),
											   .position_offset = offset,
										   });
	Asset gramophone_asset{"asset/background/start/gramophone_TVOS.png"};
	Sprite & gramophone_sprite = obj.add_component<Sprite>(
		gramophone_asset, Sprite::Data{
							  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
							  .order_in_layer = 1,
							  .size = vec2(0, 100),
							  .position_offset = offset + vec2(0, -50),
						  });
	obj.add_component<Animator>(gramophone_sprite, ivec2(64, 128), uvec2(2, 1),
								Animator::Data{
									.fps = 10,
									.looping = true,
								});
}

void StartSubScene::add_light(crepe::GameObject & obj, crepe::vec2 offset) {
	Asset light_asset{"asset/background/start/title_light_TVOS.png"};
	obj.add_component<Sprite>(light_asset, Sprite::Data{
											   .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
											   .order_in_layer = 0,
											   .size = vec2(0, 200),
											   .position_offset = offset,
										   });
	Asset light_glow_asset{"asset/background/start/lightEffect2.png"};
	obj.add_component<Sprite>(light_glow_asset,
							  Sprite::Data{
								  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
								  .order_in_layer = 1,
								  .size = vec2(0, 100),
								  .position_offset = offset + vec2(0, 75),
							  });
	Asset light_effect_asset{"asset/background/start/lightEffect.png"};
	obj.add_component<Sprite>(light_effect_asset,
							  Sprite::Data{
								  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
								  .order_in_layer = 0,
								  .size = vec2(0, 100),
								  .position_offset = offset + vec2(0, 350),
							  });
}

void StartSubScene::add_jetpack_stand(crepe::GameObject & obj, crepe::vec2 offset) {
	Asset jetpack_stand_asset{"asset/background/start/JetpackStand.png"};
	Sprite & jetpeck_stand_sprite = obj.add_component<Sprite>(
		jetpack_stand_asset, Sprite::Data{
								 .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
								 .order_in_layer = 1,
								 .size = vec2(0, 70),
								 .position_offset = offset,
							 });
	obj.add_component<Animator>(jetpeck_stand_sprite, ivec2(34, 46), uvec2(2, 1),
								Animator::Data{
									.fps = 10,
									.looping = true,
								})
		.pause();
	Asset do_not_steal = {"asset/background/start/doNotTouchSign_TVOS.png"};
	obj.add_component<Sprite>(do_not_steal,
							  Sprite::Data{
								  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
								  .order_in_layer = 1,
								  .size = vec2(0, 100),
								  .position_offset = offset + vec2(-75, -25),
							  });
}

void StartSubScene::create_wall_fragments(crepe::Scene & scn, float begin_x) {
	GameObject frag_1 = scn.new_object("frag_1", "wall_fragment", vec2(begin_x, 200));
	Asset frag_1_asset{"asset/background/start/StartWall_frag1.png"};
	Sprite & frag_1_sprite = frag_1.add_component<Sprite>(
		frag_1_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_1_sprite.active = false;
	Rigidbody & frag_1_rb = frag_1.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 10,
		.linear_velocity = vec2(400, 400),
		.linear_velocity_coefficient = vec2(0.5, 0.6),
		.angular_velocity = 500,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_1_rb.active = false;
	frag_1.add_component<CircleCollider>(25);

	GameObject frag_2 = scn.new_object("frag_2", "wall_fragment", vec2(begin_x, 180));
	Asset frag_2_asset{"asset/background/start/StartWall_frag2.png"};
	Sprite & frag_2_sprite = frag_2.add_component<Sprite>(
		frag_2_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_2_sprite.active = false;
	Rigidbody & frag_2_rb = frag_2.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 20,
		.linear_velocity = vec2(400, 400),
		.linear_velocity_coefficient = vec2(0.35, 0.4),
		.angular_velocity = 400,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_2_rb.active = false;
	frag_2.add_component<CircleCollider>(55);

	GameObject frag_3 = scn.new_object("frag_3", "wall_fragment", vec2(begin_x, 170));
	Asset frag_3_asset{"asset/background/start/StartWall_frag3.png"};
	Sprite & frag_3_sprite = frag_3.add_component<Sprite>(
		frag_3_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_3_sprite.active = false;
	Rigidbody & frag_3_rb = frag_3.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 30,
		.linear_velocity = vec2(400, 400),
		.linear_velocity_coefficient = vec2(0.3, 0.3),
		.angular_velocity = 300,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_3_rb.active = false;
	frag_3.add_component<CircleCollider>(35);

	GameObject frag_4 = scn.new_object("frag_4", "wall_fragment", vec2(begin_x, 160));
	Asset frag_4_asset{"asset/background/start/StartWall_frag4.png"};
	Sprite & frag_4_sprite = frag_4.add_component<Sprite>(
		frag_4_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_4_sprite.active = false;
	Rigidbody & frag_4_rb = frag_4.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 40,
		.linear_velocity = vec2(700, 400),
		.linear_velocity_coefficient = vec2(0.2, 0.2),
		.angular_velocity = 200,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_4_rb.active = false;
	frag_4.add_component<CircleCollider>(60);

	GameObject frag_5 = scn.new_object("frag_5", "wall_fragment", vec2(begin_x, 150));
	Asset frag_5_asset{"asset/background/start/StartWall_frag5.png"};
	Sprite & frag_5_sprite = frag_5.add_component<Sprite>(
		frag_5_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_5_sprite.active = false;
	Rigidbody & frag_5_rb = frag_5.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 50,
		.linear_velocity = vec2(600, 800),
		.linear_velocity_coefficient = vec2(0.25, 0.15),
		.angular_velocity = 100,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_5_rb.active = false;
	frag_5.add_component<CircleCollider>(5);

	GameObject frag_6 = scn.new_object("frag_6", "wall_fragment", vec2(begin_x, 140));
	Asset frag_6_asset{"asset/background/start/StartWall_frag6.png"};
	Sprite & frag_6_sprite = frag_6.add_component<Sprite>(
		frag_6_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_6_sprite.active = false;
	Rigidbody & frag_6_rb = frag_6.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 30,
		.linear_velocity = vec2(300, 800),
		.linear_velocity_coefficient = vec2(0.35, 0.25),
		.angular_velocity = 100,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_6_rb.active = false;
	frag_6.add_component<CircleCollider>(30);

	GameObject frag_7 = scn.new_object("frag_7", "wall_fragment", vec2(begin_x, 130));
	Asset frag_7_asset{"asset/background/start/StartWall_frag7.png"};
	Sprite & frag_7_sprite = frag_7.add_component<Sprite>(
		frag_7_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_7_sprite.active = false;
	Rigidbody & frag_7_rb = frag_7.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 20,
		.linear_velocity = vec2(400, 500),
		.linear_velocity_coefficient = vec2(0.45, 0.6),
		.angular_velocity = 800,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_7_rb.active = false;
	frag_7.add_component<CircleCollider>(45);

	GameObject frag_8 = scn.new_object("frag_8", "wall_fragment", vec2(begin_x, 120));
	Asset frag_8_asset{"asset/background/start/StartWall_frag8.png"};
	Sprite & frag_8_sprite = frag_8.add_component<Sprite>(
		frag_8_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_8_sprite.active = false;
	Rigidbody & frag_8_rb = frag_8.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 30,
		.linear_velocity = vec2(400, 400),
		.linear_velocity_coefficient = vec2(0.5, 0.6),
		.angular_velocity = 500,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_8_rb.active = false;
	frag_8.add_component<CircleCollider>(25);

	GameObject frag_9 = scn.new_object("frag_9", "wall_fragment", vec2(begin_x, 110));
	Asset frag_9_asset{"asset/background/start/StartWall_frag9.png"};
	Sprite & frag_9_sprite = frag_9.add_component<Sprite>(
		frag_9_asset, Sprite::Data{
						  .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						  .order_in_layer = 5,
						  .size = vec2(0, 50),
					  });
	frag_9_sprite.active = false;
	Rigidbody & frag_9_rb = frag_9.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 40,
		.linear_velocity = vec2(200, 400),
		.linear_velocity_coefficient = vec2(0.5, 0.25),
		.angular_velocity = 500,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_9_rb.active = false;
	frag_9.add_component<CircleCollider>(15);

	GameObject frag_10 = scn.new_object("frag_10", "wall_fragment", vec2(begin_x, 100));
	Asset frag_10_asset{"asset/background/start/StartWall_frag10.png"};
	Sprite & frag_10_sprite = frag_10.add_component<Sprite>(
		frag_10_asset, Sprite::Data{
						   .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						   .order_in_layer = 5,
						   .size = vec2(0, 50),
					   });
	frag_10_sprite.active = false;
	Rigidbody & frag_10_rb = frag_10.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 50,
		.linear_velocity = vec2(400, 900),
		.linear_velocity_coefficient = vec2(0.35, 0.4),
		.angular_velocity = 300,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_10_rb.active = false;
	frag_10.add_component<CircleCollider>(60);

	GameObject frag_11 = scn.new_object("frag_11", "wall_fragment", vec2(begin_x, 90));
	Asset frag_11_asset{"asset/background/start/StartWall_frag11.png"};
	Sprite & frag_11_sprite = frag_11.add_component<Sprite>(
		frag_11_asset, Sprite::Data{
						   .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						   .order_in_layer = 5,
						   .size = vec2(0, 50),
					   });
	frag_11_sprite.active = false;
	Rigidbody & frag_11_rb = frag_11.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 60,
		.linear_velocity = vec2(600, 800),
		.linear_velocity_coefficient = vec2(0.3, 0.3),
		.angular_velocity = 200,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_11_rb.active = false;
	frag_11.add_component<CircleCollider>(5);

	GameObject frag_12 = scn.new_object("frag_12", "wall_fragment", vec2(begin_x, 80));
	Asset frag_12_asset{"asset/background/start/StartWall_frag12.png"};
	Sprite & frag_12_sprite = frag_12.add_component<Sprite>(
		frag_12_asset, Sprite::Data{
						   .sorting_in_layer = SORT_IN_LAY_FORE_BACKGROUND,
						   .order_in_layer = 5,
						   .size = vec2(0, 50),
					   });
	frag_12_sprite.active = false;
	Rigidbody & frag_12_rb = frag_12.add_component<Rigidbody>(Rigidbody::Data{
		.gravity_scale = 70,
		.linear_velocity = vec2(500, 800),
		.linear_velocity_coefficient = vec2(0.25, 0.15),
		.angular_velocity = 100,
		.angular_velocity_coefficient = 0.55,
		.elasticity_coefficient = 0.5,
		.collision_layer = 5,
	});
	frag_12_rb.active = false;
	frag_12.add_component<CircleCollider>(50);

	GameObject smoke_particles_1
		= scn.new_object("smoke_particles", "particle_emitter", vec2(begin_x - 100, 200));
	Asset smoke_asset_1{"asset/particles/smoke.png"};
	Sprite & smoke_sprite_1 = smoke_particles_1.add_component<Sprite>(
		smoke_asset_1, Sprite::Data{
						   .color = Color(255, 255, 255, 50),
						   .sorting_in_layer = SORT_IN_LAY_PARTICLES_FOREGROUND,
						   .order_in_layer = 0,
						   .size = vec2(0, 100),
					   });
	ParticleEmitter & emitter_1 = smoke_particles_1.add_component<ParticleEmitter>(
		smoke_sprite_1, ParticleEmitter::Data{
							.emission_rate = 20,
							.min_speed = 40,
							.max_speed = 100,
							.min_angle = -30,
							.max_angle = 10,
							.end_lifespan = 4,
						});
	emitter_1.active = false;

	GameObject smoke_particles_2
		= scn.new_object("smoke_particles", "particle_emitter", vec2(begin_x - 100, 200));
	Asset smoke_asset_2{"asset/particles/smoke.png"};
	Sprite & smoke_sprite_2 = smoke_particles_2.add_component<Sprite>(
		smoke_asset_2, Sprite::Data{
						   .color = Color(255, 255, 255, 50),
						   .sorting_in_layer = SORT_IN_LAY_PARTICLES_FOREGROUND,
						   .order_in_layer = 0,
						   .size = vec2(0, 70),
					   });
	ParticleEmitter & emitter_2 = smoke_particles_2.add_component<ParticleEmitter>(
		smoke_sprite_2, ParticleEmitter::Data{
							.emission_rate = 30,
							.min_speed = 40,
							.max_speed = 100,
							.min_angle = -45,
							.max_angle = 5,
							.end_lifespan = 3,
						});
	emitter_2.active = false;
}
