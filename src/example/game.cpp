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

using namespace crepe;
using namespace std;

class Background {
public:
	Background(ComponentManager & mgr) {
		this->start(mgr);

		this->hallway(mgr);

		this->forest(mgr);

		this->aquarium(mgr);

		this->forest(mgr);
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

	void add_lamp_start(GameObject & obj, vec2 offset) {
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
										.fps = 10,
										.looping = true,
									});
	}

	void hallway(ComponentManager & mgr) {
		GameObject begin = mgr.new_object("hallway_begin", "background", vec2(begin_x, 0));
		Asset begin_asset{"asset/jetpack_joyride/background/hallway/hallway1FG_1_TVOS.png"};
		begin.add_component<Sprite>(begin_asset, Sprite::Data{
													 .sorting_in_layer = 4,
													 .order_in_layer = 0,
													 .size = vec2(0, 800),
												 });
		begin_x += 600;

		// Atributes for begin

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

	void forest(ComponentManager & mgr) {
		GameObject forest_begin
			= mgr.new_object("forest_begin", "background", vec2(begin_x, 0));
		Asset forest_begin_asset{
			"asset/jetpack_joyride/background/forest/forestFG_1_TVOS.png"};
		forest_begin.add_component<Sprite>(forest_begin_asset, Sprite::Data{
																   .sorting_in_layer = 4,
																   .order_in_layer = 0,
																   .size = vec2(0, 800),
															   });
		begin_x += 800;

		GameObject forest_middle
			= mgr.new_object("forest_middle", "background", vec2(begin_x, 0));
		Asset forest_middle_asset{
			"asset/jetpack_joyride/background/forest/forestFG_3_TVOS.png"};
		forest_middle.add_component<Sprite>(forest_middle_asset, Sprite::Data{
																	 .sorting_in_layer = 4,
																	 .order_in_layer = 2,
																	 .size = vec2(0, 800),
																 });
		begin_x += 800;

		GameObject forest_end = mgr.new_object("forest_end", "background", vec2(begin_x, 0));
		Asset forest_end_asset{"asset/jetpack_joyride/background/forest/forestFG_2_TVOS.png"};
		forest_end.add_component<Sprite>(forest_end_asset, Sprite::Data{
															   .sorting_in_layer = 4,
															   .order_in_layer = 1,
															   .size = vec2(0, 800),
														   });
		begin_x += 600;
	}

	void aquarium(ComponentManager & mgr) {
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

		GameObject aquarium_middle
			= mgr.new_object("aquarium_middle", "background", vec2(begin_x, 0));
		Asset aquarium_middle_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_3_TVOS.png"};
		aquarium_middle.add_component<Sprite>(aquarium_middle_asset, Sprite::Data{
																		 .sorting_in_layer = 4,
																		 .order_in_layer = 2,
																		 .size = vec2(0, 800),
																	 });
		begin_x += 600;

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
	}

	string get_name() const { return "scene1"; }
};

int main(int argc, char * argv[]) {
	LoopManager gameloop;
	gameloop.add_scene<Scene1>();
	gameloop.start();
	return 0;
}
