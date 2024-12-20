#include "GameScene.h"

#include <crepe/api/Engine.h>
#include <crepe/api/Script.h>

using namespace crepe;
using namespace std;

class ScriptBox : public Script {
public:
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Box {} on_collision() with {}", test.info.self.metadata.game_object_id,
				  test.info.other.metadata.game_object_id);
		return true;
	}

	void init() {
		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->oncollision(ev); });
	}
};

class ScriptCircle : public Script {
public:
	bool oncollision(const CollisionEvent & test) {
		Log::logf("Circle {} on_collision() with {}", test.info.self.metadata.game_object_id,
				  test.info.other.metadata.game_object_id);
		return true;
	}

	void init() {
		subscribe<CollisionEvent>(
			[this](const CollisionEvent & ev) -> bool { return this->oncollision(ev); });
	}
};

class ScriptMoveToLeft : public Script {
public:
	void update() {
		Transform & transform = this->get_component<Transform>();
		transform.position.x -= 0.02;
	}
};

class ScriptMoveToRight : public Script {
public:
	void update() {
		Transform & transform = this->get_component<Transform>();
		transform.position.x += 0.02;
	}
};

class ConcreteScene1 : public Scene {
public:
	void load_scene() {
		GameObject camera = this->new_object("camera");
		camera.add_component<Camera>(ivec2(1080, 720), vec2(10, 10),
									 Camera::Data{.bg_color = Color::WHITE, .zoom = 1});

		GameObject reference = this->new_object("reference", "tag", vec2(0, 0), 0, 1);
		Asset reference_asset = Asset("asset/texture/square.png");
		reference.add_component<Sprite>(reference_asset, Sprite::Data{
															 .color = Color::RED,
															 .sorting_in_layer = 10,
															 .order_in_layer = 0,
															 .size = vec2(0.1, 0.1),
															 .angle_offset = 0,
															 .scale_offset = 1,
															 .position_offset = vec2(0, 0),
														 });

		/*GameObject box_1 = this->new_object("box_1", "tag", vec2(0, 0), 0, 1);
		Asset box_1_asset = Asset("asset/texture/square.png");
		box_1.add_component<Sprite>(box_1_asset, Sprite::Data{
			.sorting_in_layer = 0,
			.order_in_layer = 0,
			.size = vec2(1, 1),
			.angle_offset = 0,
			.scale_offset = 1,
			.position_offset = vec2(0, 0.5),
		});
		Asset box_1_asset2 = Asset("asset/texture/test_ap43.png");
		box_1.add_component<Sprite>(box_1_asset2, Sprite::Data{
			.sorting_in_layer = 0,
			.order_in_layer = 0,
			.size = vec2(1, 1),
			.angle_offset = 0,
			.scale_offset = 1,
			.position_offset = vec2(0, -0.5),
		});*/

		/*GameObject particles = this->new_object("particles", "tag", vec2(-1, 0), 180, 1);
		Asset particles_asset = Asset("asset/texture/test_ap43.png");
		Sprite & particles_sprite = particles.add_component<Sprite>(particles_asset, Sprite::Data{
			.sorting_in_layer = 0,
			.order_in_layer = 0,
			.size = vec2(1, 1),
			.angle_offset = 0,
			.scale_offset = 1,
			.position_offset = vec2(0, 0),
		});
		ParticleEmitter & particles_emitter = particles.add_component<ParticleEmitter>(particles_sprite, ParticleEmitter::Data{
			.offset = vec2(0, 0),
			.emission_rate = 1,
			.min_speed = 1,
			.max_speed = 1,
			.min_angle = 0,
			.max_angle = 0,
			.end_lifespan = 4,
		});*/

		const bool SCRIPT = false;

		const Rigidbody::BodyType BODYTYPE_LEFT = Rigidbody::BodyType::DYNAMIC;
		const Rigidbody::BodyType BODYTYPE_RIGHT = Rigidbody::BodyType::DYNAMIC;
		const bool BOUNCE_LEFT = false;
		const bool BOUNCE_RIGHT = false;
		const bool KINEMATIC_COLLISION = true;
		const bool ONTOP = false;

		const float SCALE = 0.5;
		const float OFFSET_X_LEFT = 0;
		const float OFFSET_X_RIGHT = 0;
		const float OFFSET_Y_LEFT = 0;
		const float OFFSET_Y_RIGHT = 0;

		GameObject box_1 = this->new_object("box_1", "tag",
											ONTOP ? vec2(-0.25, -4) : vec2(-2, -4), 0, SCALE);
		Asset box_1_asset = Asset("asset/texture/square.png");
		box_1.add_component<Sprite>(box_1_asset,
									Sprite::Data{
										.sorting_in_layer = 0,
										.order_in_layer = 0,
										.size = vec2(1, 1),
										.angle_offset = 0,
										.scale_offset = 1,
										.position_offset = vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT),
									});
		box_1.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_LEFT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{1, 0},
			.elasticity_coefficient = BOUNCE_LEFT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		box_1.add_component<BehaviorScript>().set_script<ScriptMoveToRight>().active = SCRIPT;
		box_1.add_component<BoxCollider>(vec2(1, 1), vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT));
		box_1.add_component<BehaviorScript>().set_script<ScriptBox>();

		GameObject circle_1 = this->new_object("ricle_1", "tag",
											   ONTOP ? vec2(0.25, -4) : vec2(2, -4), 0, SCALE);
		Asset circle_1_asset = Asset("asset/texture/circle.png");
		circle_1.add_component<Sprite>(
			circle_1_asset, Sprite::Data{
								.sorting_in_layer = 0,
								.order_in_layer = 0,
								.size = vec2(1, 1),
								.angle_offset = 0,
								.scale_offset = 1,
								.position_offset = vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT),
							});
		circle_1.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_RIGHT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{-1, 0},
			.elasticity_coefficient = BOUNCE_RIGHT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		circle_1.add_component<BehaviorScript>().set_script<ScriptMoveToLeft>().active
			= SCRIPT;
		circle_1.add_component<CircleCollider>(0.5, vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT));
		circle_1.add_component<BehaviorScript>().set_script<ScriptCircle>();

		GameObject circle_2 = this->new_object(
			"ricle_2", "tag", ONTOP ? vec2(-0.25, -1.5) : vec2(-2.5, -1.5), 0, SCALE);
		Asset circle_2_asset = Asset("asset/texture/circle.png");
		circle_2.add_component<Sprite>(
			circle_2_asset, Sprite::Data{
								.sorting_in_layer = 0,
								.order_in_layer = 0,
								.size = vec2(1, 1),
								.angle_offset = 0,
								.scale_offset = 1,
								.position_offset = vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT),
							});
		circle_2.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_LEFT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{1, 0},
			.elasticity_coefficient = BOUNCE_LEFT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		circle_2.add_component<BehaviorScript>().set_script<ScriptMoveToRight>().active
			= SCRIPT;
		circle_2.add_component<CircleCollider>(0.5, vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT));
		circle_2.add_component<BehaviorScript>().set_script<ScriptCircle>();

		GameObject box_2 = this->new_object(
			"box_2", "tag", ONTOP ? vec2(0.25, -1.5) : vec2(2.5, -1.5), 0, SCALE);
		Asset box_2_asset = Asset("asset/texture/square.png");
		box_2.add_component<Sprite>(
			box_2_asset, Sprite::Data{
							 .sorting_in_layer = 0,
							 .order_in_layer = 0,
							 .size = vec2(1, 1),
							 .angle_offset = 0,
							 .scale_offset = 1,
							 .position_offset = vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT),
						 });
		box_2.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_RIGHT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{-1, 0},
			.elasticity_coefficient = BOUNCE_RIGHT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		box_2.add_component<BehaviorScript>().set_script<ScriptMoveToLeft>().active = SCRIPT;
		box_2.add_component<BoxCollider>(vec2(1, 1), vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT));
		box_2.add_component<BehaviorScript>().set_script<ScriptBox>();

		GameObject box_3 = this->new_object(
			"box_3", "tag", ONTOP ? vec2(-0.25, 1.5) : vec2(-3, 1.5), 0, SCALE);
		Asset box_3_asset = Asset("asset/texture/square.png");
		box_3.add_component<Sprite>(box_3_asset,
									Sprite::Data{
										.sorting_in_layer = 0,
										.order_in_layer = 0,
										.size = vec2(1, 1),
										.angle_offset = 0,
										.scale_offset = 1,
										.position_offset = vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT),
									});
		box_3.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_LEFT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{1, 0},
			.elasticity_coefficient = BOUNCE_LEFT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		box_3.add_component<BehaviorScript>().set_script<ScriptMoveToRight>().active = SCRIPT;
		box_3.add_component<BoxCollider>(vec2(1, 1), vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT));
		box_3.add_component<BehaviorScript>().set_script<ScriptBox>();

		GameObject box_4 = this->new_object("box_4", "tag",
											ONTOP ? vec2(0.25, 1.5) : vec2(3, 1.5), 0, SCALE);
		Asset box_4_asset = Asset("asset/texture/square.png");
		box_4.add_component<Sprite>(
			box_4_asset, Sprite::Data{
							 .sorting_in_layer = 0,
							 .order_in_layer = 0,
							 .size = vec2(1, 1),
							 .angle_offset = 0,
							 .scale_offset = 1,
							 .position_offset = vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT),
						 });
		box_4.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_RIGHT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{-1, 0},
			.elasticity_coefficient = BOUNCE_RIGHT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		box_4.add_component<BehaviorScript>().set_script<ScriptMoveToLeft>().active = SCRIPT;
		box_4.add_component<BoxCollider>(vec2(1, 1), vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT));
		box_4.add_component<BehaviorScript>().set_script<ScriptBox>();

		GameObject circle_3 = this->new_object(
			"ricle_3", "tag", ONTOP ? vec2(-0.25, 4) : vec2(-3.5, 4), 0, SCALE);
		Asset circle_3_asset = Asset("asset/texture/circle.png");
		circle_3.add_component<Sprite>(
			circle_3_asset, Sprite::Data{
								.sorting_in_layer = 0,
								.order_in_layer = 0,
								.size = vec2(1, 1),
								.angle_offset = 0,
								.scale_offset = 1,
								.position_offset = vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT),
							});
		circle_3.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_LEFT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{1, 0},
			.elasticity_coefficient = BOUNCE_LEFT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		circle_3.add_component<BehaviorScript>().set_script<ScriptMoveToRight>().active
			= SCRIPT;
		circle_3.add_component<CircleCollider>(0.5, vec2(OFFSET_X_LEFT, OFFSET_Y_LEFT));
		circle_3.add_component<BehaviorScript>().set_script<ScriptCircle>();

		GameObject circle_4 = this->new_object("ricle_4", "tag",
											   ONTOP ? vec2(0.25, 4) : vec2(3.5, 4), 0, SCALE);
		Asset circle_4_asset = Asset("asset/texture/circle.png");
		circle_4.add_component<Sprite>(
			circle_4_asset, Sprite::Data{
								.sorting_in_layer = 0,
								.order_in_layer = 0,
								.size = vec2(1, 1),
								.angle_offset = 0,
								.scale_offset = 1,
								.position_offset = vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT),
							});
		circle_4.add_component<Rigidbody>(Rigidbody::Data{
			.gravity_scale = 0,
			.body_type = BODYTYPE_RIGHT,
			.linear_velocity = SCRIPT ? vec2{0, 0} : vec2{-1, 0},
			.elasticity_coefficient = BOUNCE_RIGHT ? 0.5 : 0,
			.kinematic_collision = KINEMATIC_COLLISION,
		});
		circle_4.add_component<BehaviorScript>().set_script<ScriptMoveToLeft>().active
			= SCRIPT;
		circle_4.add_component<CircleCollider>(0.5, vec2(OFFSET_X_RIGHT, OFFSET_Y_RIGHT));
		circle_4.add_component<BehaviorScript>().set_script<ScriptCircle>();
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {
	Engine gameloop;
	gameloop.add_scene<GameScene>();

	return gameloop.main();
}
