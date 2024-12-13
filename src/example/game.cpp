#include "api/Animator.h"
#include "api/BehaviorScript.h"
#include "api/CircleCollider.h"
#include "api/Scene.h"
#include "manager/ComponentManager.h"
#include "manager/Mediator.h"
#include "types.h"
#include <crepe/api/Asset.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <iostream>

using namespace crepe;
using namespace std;

class ParallaxScript : public Script {
public:
	ParallaxScript(float begin_x, float end_x, std::string unique_bg_name)
		: begin_x(begin_x),
		  end_x(end_x),
		  name(unique_bg_name) {}

	void update() {
		RefVector<Transform> vec_2
			= this->get_components_by_name<Transform>("forest_bg_2_" + name);
		RefVector<Transform> vec_3
			= this->get_components_by_name<Transform>("forest_bg_3_" + name);

		for (Transform & t : vec_2) {
			if (t.position.x < begin_x - 400) {
				t.position.x = end_x - 400;
			}
		}
		for (Transform & t : vec_3) {
			if (t.position.x < begin_x - 400) {
				t.position.x = end_x - 400;
			}
		}
	}

private:
	const float begin_x;
	const float end_x;
	const std::string name;
};

class Background {
public:
	Background(ComponentManager & mgr) {
		this->start(mgr);

		this->hallway(mgr, 1, Color::YELLOW);

		this->forest(mgr, "1");

		this->hallway(mgr, 2, Color::MAGENTA);

		this->aquarium(mgr);

		this->hallway(mgr, 3, Color::CYAN);

		this->forest(mgr, "2");

		this->hallway(mgr, 4, Color::GREEN);

		this->aquarium(mgr);
	}

	void start(ComponentManager & mgr) {
		GameObject begin = mgr.new_object("start_begin", "background", vec2(begin_x, 0));
		Asset begin_asset{"asset/jetpack_joyride/background/start/titleFG_1_TVOS.png"};
		begin.add_component<Sprite>(begin_asset, Sprite::Data{
													 .sorting_in_layer = 4,
													 .order_in_layer = 0,
													 .size = vec2(0, 800),
												 });
		begin_x += 700;

		GameObject end = mgr.new_object("start_end", "background", vec2(begin_x, 0));
		Asset end_asset{"asset/jetpack_joyride/background/start/titleFG_2_TVOS.png"};
		end.add_component<Sprite>(end_asset, Sprite::Data{
												 .sorting_in_layer = 4,
												 .order_in_layer = 1,
												 .size = vec2(0, 800),
											 });
		begin_x += 100;

		this->add_lamp_start(end, vec2(-350, -95));
	}

	void add_lamp_start(GameObject & obj, vec2 offset, unsigned int fps = 10) {
		Asset lamp_asset{"asset/jetpack_joyride/background/start/alarmLight_TVOS.png"};
		obj.add_component<Sprite>(lamp_asset, Sprite::Data{
												  .sorting_in_layer = 5,
												  .order_in_layer = 0,
												  .size = vec2(0, 100),
												  .position_offset = offset,
											  });
		Asset lamp_glow_asset{"asset/jetpack_joyride/background/start/alarmGlow_TVOS.png"};
		Sprite & lamp_glow_sprite = obj.add_component<Sprite>(
			lamp_glow_asset, Sprite::Data{
								 .sorting_in_layer = 5,
								 .order_in_layer = 1,
								 .size = vec2(0, 300),
								 .position_offset = offset - vec2(65, -55),
							 });
		obj.add_component<Animator>(lamp_glow_sprite, ivec2(422, 384), uvec2(6, 1),
									Animator::Data{
										.fps = fps,
										.looping = true,
									});
	}

	void hallway(ComponentManager & mgr, unsigned int sector_num, Color sector_color) {
		GameObject begin = mgr.new_object("hallway_begin", "background", vec2(begin_x, 0));
		Asset begin_asset{"asset/jetpack_joyride/background/hallway/hallway1FG_1_TVOS.png"};
		begin.add_component<Sprite>(begin_asset, Sprite::Data{
													 .sorting_in_layer = 4,
													 .order_in_layer = 0,
													 .size = vec2(0, 800),
												 });
		begin_x += 600;

		this->add_sector_number_hallway(begin, vec2(-200, 0), sector_num, sector_color);
		this->add_lamp_hallway(begin, vec2(-70, -120), 11);
		this->add_lamp_hallway(begin, vec2(30, -120), 9);

		GameObject middle_1 = mgr.new_object("hallway_middle", "background", vec2(begin_x, 0));
		Asset middle_asset{"asset/jetpack_joyride/background/hallway/hallway1FG_2_TVOS.png"};
		middle_1.add_component<Sprite>(middle_asset, Sprite::Data{
														 .sorting_in_layer = 4,
														 .order_in_layer = 2,
														 .size = vec2(0, 800),
													 });
		begin_x += 600;

		GameObject middle_2 = mgr.new_object("hallway_middle", "background", vec2(begin_x, 0));
		Asset middle_asset_2{"asset/jetpack_joyride/background/hallway/hallway1FG_2_TVOS.png"};
		middle_2.add_component<Sprite>(middle_asset_2, Sprite::Data{
														   .sorting_in_layer = 4,
														   .order_in_layer = 3,
														   .size = vec2(0, 800),
													   });
		begin_x += 200;

		GameObject middle_3 = mgr.new_object("hallway_middle", "background", vec2(begin_x, 0));
		Asset middle_asset_3{"asset/jetpack_joyride/background/hallway/hallway1FG_2_TVOS.png"};
		middle_3.add_component<Sprite>(middle_asset_3, Sprite::Data{
														   .sorting_in_layer = 4,
														   .order_in_layer = 4,
														   .size = vec2(0, 800),
													   });
		begin_x += 400;

		this->add_lamp_hallway(middle_3, vec2(0, -120));

		GameObject middle_4 = mgr.new_object("hallway_middle", "background", vec2(begin_x, 0));
		Asset middle_asset_4{"asset/jetpack_joyride/background/hallway/hallway1FG_2_TVOS.png"};
		middle_4.add_component<Sprite>(middle_asset_4, Sprite::Data{
														   .sorting_in_layer = 4,
														   .order_in_layer = 5,
														   .size = vec2(0, 800),
													   });
		begin_x += 600;

		GameObject end = mgr.new_object("hallway_end", "background", vec2(begin_x, 0));
		Asset end_asset{"asset/jetpack_joyride/background/hallway/hallway1FG_1_TVOS.png"};
		end.add_component<Sprite>(end_asset, Sprite::Data{
												 .sorting_in_layer = 4,
												 .order_in_layer = 1,
												 .size = vec2(0, 800),
											 });
		begin_x += 600;
	}

	void add_lamp_hallway(GameObject & obj, vec2 offset, unsigned int fps = 10) {
		Asset lamp_asset{"asset/jetpack_joyride/background/hallway/alarmLight_TVOS.png"};
		obj.add_component<Sprite>(lamp_asset, Sprite::Data{
												  .sorting_in_layer = 5,
												  .order_in_layer = 0,
												  .size = vec2(0, 100),
												  .position_offset = offset,
											  });
		Asset lamp_glow_asset{"asset/jetpack_joyride/background/hallway/alarmGlow_TVOS.png"};
		Sprite & lamp_glow_sprite = obj.add_component<Sprite>(
			lamp_glow_asset, Sprite::Data{
								 .sorting_in_layer = 5,
								 .order_in_layer = 1,
								 .size = vec2(0, 300),
								 .position_offset = offset - vec2(65, -30),
							 });
		obj.add_component<Animator>(lamp_glow_sprite, ivec2(422, 384), uvec2(6, 1),
									Animator::Data{
										.fps = fps,
										.looping = true,
									});
	}

	void add_sector_number_hallway(GameObject & obj, vec2 offset, unsigned int sector_num,
								   Color sector_color) {
		Asset sector_text_asset{
			"asset/jetpack_joyride/background/hallway/sectorText_TVOS.png"};
		obj.add_component<Sprite>(sector_text_asset, Sprite::Data{
														 .color = sector_color,
														 .sorting_in_layer = 5,
														 .order_in_layer = 0,
														 .size = vec2(0, 100),
														 .position_offset = offset,
													 });
		Asset sector_num_asset{
			"asset/jetpack_joyride/background/hallway/sectorNumbers_TVOS.png"};
		Sprite & sector_num_sprite = obj.add_component<Sprite>(
			sector_num_asset, Sprite::Data{
								  .color = sector_color,
								  .sorting_in_layer = 5,
								  .order_in_layer = 0,
								  .size = vec2(0, 100),
								  .position_offset = offset + vec2(200, 0),
							  });
		Animator & sector_num_anim = obj.add_component<Animator>(
			sector_num_sprite, ivec2(256, 128), uvec2(4, 4), Animator::Data{});
		int column = (sector_num - 1) / 4;
		int row = (sector_num - 1) % 4;
		sector_num_anim.set_anim(column);
		for (int i = 0; i < row; i++) {
			sector_num_anim.next_anim();
		}
		sector_num_anim.pause();
	}

	void forest(ComponentManager & mgr, std::string unique_bg_name) {
		GameObject script = mgr.new_object("forest_script", "background");
		script.add_component<BehaviorScript>().set_script<ParallaxScript>(
			begin_x - 400, begin_x + 3000 + 400, unique_bg_name);

		this->add_background_forest(mgr, begin_x, unique_bg_name);

		GameObject begin = mgr.new_object("forest_begin", "background", vec2(begin_x, 0));
		Asset begin_asset{"asset/jetpack_joyride/background/forest/forestFG_1_TVOS.png"};
		begin.add_component<Sprite>(begin_asset, Sprite::Data{
													 .sorting_in_layer = 4,
													 .order_in_layer = 0,
													 .size = vec2(0, 800),
												 });
		begin_x += 800;

		this->add_background_forest(mgr, begin_x, unique_bg_name);

		GameObject middle_1 = mgr.new_object("forest_middle", "background", vec2(begin_x, 0));
		Asset middle_1_asset{"asset/jetpack_joyride/background/forest/forestFG_3_TVOS.png"};
		middle_1.add_component<Sprite>(middle_1_asset, Sprite::Data{
														   .sorting_in_layer = 4,
														   .order_in_layer = 2,
														   .size = vec2(0, 800),
													   });
		begin_x += 800;

		this->add_background_forest(mgr, begin_x, unique_bg_name);

		GameObject middle_2 = mgr.new_object("forest_middle", "background", vec2(begin_x, 0));
		Asset middle_2_asset{"asset/jetpack_joyride/background/forest/forestFG_3_TVOS.png"};
		middle_2.add_component<Sprite>(middle_2_asset, Sprite::Data{
														   .sorting_in_layer = 4,
														   .order_in_layer = 3,
														   .size = vec2(0, 800),
													   });
		begin_x += 800;

		this->add_background_forest(mgr, begin_x, unique_bg_name);

		GameObject end = mgr.new_object("forest_end", "background", vec2(begin_x, 0));
		Asset end_asset{"asset/jetpack_joyride/background/forest/forestFG_2_TVOS.png"};
		end.add_component<Sprite>(end_asset, Sprite::Data{
												 .sorting_in_layer = 4,
												 .order_in_layer = 1,
												 .size = vec2(0, 800),
											 });
		begin_x += 600;

		this->add_background_forest(mgr, begin_x + 200, unique_bg_name);
	}

	void add_background_forest(ComponentManager & mgr, float begin_x, std::string name) {
		GameObject bg_1
			= mgr.new_object("forest_bg_1_" + name, "forest_background", vec2(begin_x, 0));
		Asset bg_1_asset{"asset/jetpack_joyride/background/forest/forestBG1_1_TVOS.png"};
		bg_1.add_component<Sprite>(bg_1_asset, Sprite::Data{
												   .sorting_in_layer = 3,
												   .order_in_layer = 2,
												   .size = vec2(0, 800),
											   });
		GameObject bg_2
			= mgr.new_object("forest_bg_2_" + name, "forest_background", vec2(begin_x, 0));
		Asset bg_2_1_asset{"asset/jetpack_joyride/background/forest/forestBG2_1_TVOS.png"};
		bg_2.add_component<Sprite>(bg_2_1_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 1,
													 .size = vec2(0, 400),
													 .position_offset = vec2(200, 0),
												 });
		Asset bg_2_2_asset{"asset/jetpack_joyride/background/forest/forestBG2_2_TVOS.png"};
		bg_2.add_component<Sprite>(bg_2_2_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 1,
													 .size = vec2(0, 400),
													 .position_offset = vec2(-200, 0),
												 });
		GameObject bg_3
			= mgr.new_object("forest_bg_3_" + name, "forest_background", vec2(begin_x, 0));
		Asset bg_3_1_asset{"asset/jetpack_joyride/background/forest/forestBG3_1_TVOS.png"};
		bg_3.add_component<Sprite>(bg_3_1_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 0,
													 .size = vec2(0, 200),
													 .position_offset = vec2(300, 0),
												 });
		Asset bg_3_2_asset{"asset/jetpack_joyride/background/forest/forestBG3_2_TVOS.png"};
		bg_3.add_component<Sprite>(bg_3_2_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 0,
													 .size = vec2(0, 200),
													 .position_offset = vec2(100, 0),
												 });
		Asset bg_3_3_asset{"asset/jetpack_joyride/background/forest/forestBG3_3_TVOS.png"};
		bg_3.add_component<Sprite>(bg_3_3_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 0,
													 .size = vec2(0, 200),
													 .position_offset = vec2(-100, 0),
												 });
		Asset bg_3_4_asset{"asset/jetpack_joyride/background/forest/forestBG3_4_TVOS.png"};
		bg_3.add_component<Sprite>(bg_3_4_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 0,
													 .size = vec2(0, 200),
													 .position_offset = vec2(-300, 0),
												 });

		bg_2.add_component<Rigidbody>(Rigidbody::Data{
			.linear_velocity = vec2(-0.5, 0),
		});
		bg_3.add_component<Rigidbody>(Rigidbody::Data{
			.linear_velocity = vec2(-0.25, 0),
		});
	}

	void aquarium(ComponentManager & mgr) {
		this->add_background_aquarium(mgr, begin_x);

		GameObject aquarium_begin
			= mgr.new_object("aquarium_begin", "background", vec2(begin_x, 0));
		Asset aquarium_begin_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_1_TVOS.png"};
		aquarium_begin.add_component<Sprite>(aquarium_begin_asset, Sprite::Data{
																	   .sorting_in_layer = 4,
																	   .order_in_layer = 0,
																	   .size = vec2(0, 800),
																   });
		begin_x += 600;

		GameObject aquarium_middle_1
			= mgr.new_object("aquarium_middle", "background", vec2(begin_x, 0));
		Asset aquarium_middle_1_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_3_TVOS.png"};
		aquarium_middle_1.add_component<Sprite>(aquarium_middle_1_asset,
												Sprite::Data{
													.sorting_in_layer = 4,
													.order_in_layer = 2,
													.size = vec2(0, 800),
												});
		begin_x += 400;

		this->add_background_aquarium(mgr, begin_x - 200);

		GameObject aquarium_middle_2
			= mgr.new_object("aquarium_middle", "background", vec2(begin_x, 0));
		Asset aquarium_middle_2_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_3_TVOS.png"};
		aquarium_middle_2.add_component<Sprite>(aquarium_middle_2_asset,
												Sprite::Data{
													.sorting_in_layer = 4,
													.order_in_layer = 3,
													.size = vec2(0, 800),
												});
		begin_x += 400;

		GameObject aquarium_middle_3
			= mgr.new_object("aquarium_middle", "background", vec2(begin_x, 0));
		Asset aquarium_middle_3_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_3_TVOS.png"};
		aquarium_middle_3.add_component<Sprite>(aquarium_middle_3_asset,
												Sprite::Data{
													.sorting_in_layer = 4,
													.order_in_layer = 4,
													.size = vec2(0, 800),
												});
		begin_x += 400;

		this->add_background_aquarium(mgr, begin_x - 200);

		GameObject aquarium_middle_4
			= mgr.new_object("aquarium_middle", "background", vec2(begin_x, 0));
		Asset aquarium_middle_4_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_3_TVOS.png"};
		aquarium_middle_4.add_component<Sprite>(aquarium_middle_4_asset,
												Sprite::Data{
													.sorting_in_layer = 4,
													.order_in_layer = 5,
													.size = vec2(0, 800),
												});
		begin_x += 600;

		this->add_background_aquarium(mgr, begin_x);

		GameObject aquarium_end
			= mgr.new_object("aquarium_end", "background", vec2(begin_x, 0));
		Asset aquarium_end_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_2_TVOS.png"};
		aquarium_end.add_component<Sprite>(aquarium_end_asset, Sprite::Data{
																   .sorting_in_layer = 4,
																   .order_in_layer = 1,
																   .size = vec2(0, 800),
															   });
		begin_x += 600;
	}

	void add_background_aquarium(ComponentManager & mgr, float begin_x) {
		GameObject bg_1
			= mgr.new_object("aquarium_bg_1", "aquarium_background", vec2(begin_x, 0));
		Asset bg_1_1_asset{"asset/jetpack_joyride/background/aquarium/AquariumBG1_1_TVOS.png"};
		bg_1.add_component<Sprite>(bg_1_1_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 2,
													 .size = vec2(0, 400),
													 .position_offset = vec2(-200, 100),
												 });
		Asset bg_1_2_asset{"asset/jetpack_joyride/background/aquarium/AquariumBG1_2_TVOS.png"};
		bg_1.add_component<Sprite>(bg_1_2_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 2,
													 .size = vec2(0, 400),
													 .position_offset = vec2(200, 100),
												 });
		GameObject bg_2
			= mgr.new_object("aquarium_bg_2", "aquarium_background", vec2(begin_x, 0));
		Asset bg_2_1_asset{"asset/jetpack_joyride/background/aquarium/AquariumBG2_1_TVOS.png"};
		bg_2.add_component<Sprite>(bg_2_1_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 1,
													 .size = vec2(0, 400),
													 .position_offset = vec2(200, -50),
												 });
		Asset bg_2_2_asset{"asset/jetpack_joyride/background/aquarium/AquariumBG2_2_TVOS.png"};
		bg_2.add_component<Sprite>(bg_2_2_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 1,
													 .size = vec2(0, 400),
													 .position_offset = vec2(-200, -50),
												 });
		GameObject bg_3
			= mgr.new_object("aquarium_bg_3", "aquarium_background", vec2(begin_x, 0));
		Asset bg_3_1_asset{"asset/jetpack_joyride/background/aquarium/AquariumBG3_1_TVOS.png"};
		bg_3.add_component<Sprite>(bg_3_1_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 0,
													 .size = vec2(0, 400),
													 .position_offset = vec2(200, -200),
												 });
		Asset bg_3_2_asset{"asset/jetpack_joyride/background/aquarium/AquariumBG3_2_TVOS.png"};
		bg_3.add_component<Sprite>(bg_3_2_asset, Sprite::Data{
													 .sorting_in_layer = 3,
													 .order_in_layer = 0,
													 .size = vec2(0, 400),
													 .position_offset = vec2(-200, -200),
												 });
	}

private:
	float begin_x = 0;
};

class MoveCameraScript : public Script {
public:
	void init() {
		subscribe<KeyPressEvent>(
			[this](const KeyPressEvent & ev) -> bool { return this->keypressed(ev); });
	}

private:
	bool keypressed(const KeyPressEvent & event) {
		if (event.key == Keycode::RIGHT) {
			Transform & cam = this->get_components_by_name<Transform>("camera").front();
			cam.position.x += 100;
		} else if (event.key == Keycode::LEFT) {
			Transform & cam = this->get_components_by_name<Transform>("camera").front();
			cam.position.x -= 100;
		}
		return true;
	}
};

class Scene1 : public Scene {
public:
	void load_scene() {
		Mediator & m = this->mediator;
		ComponentManager & mgr = m.component_manager;

		Background background(mgr);

		GameObject camera = mgr.new_object("camera", "camera", vec2(600, 0));
		camera.add_component<Camera>(ivec2(1700, 720), vec2(2000, 800),
									 Camera::Data{
										 .bg_color = Color::RED,
									 });
		camera.add_component<BehaviorScript>().set_script<MoveCameraScript>();
		camera.add_component<Rigidbody>(Rigidbody::Data{
			.linear_velocity = vec2(2.5, 0),
		});
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {
	LoopManager gameloop;
	gameloop.add_scene<Scene1>();
	gameloop.start();
	return 0;
}
