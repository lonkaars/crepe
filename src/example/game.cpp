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
		GameObject start_begin = mgr.new_object("start_begin", "background", vec2(0, 0));
		Asset start_begin_asset{"asset/jetpack_joyride/background/start/titleFG_1_TVOS.png"};
		start_begin.add_component<Sprite>(start_begin_asset, Sprite::Data{
																 .sorting_in_layer = 0,
																 .order_in_layer = 1,
																 .size = vec2(0, 800),
															 });

		GameObject start_end = mgr.new_object("start_end", "background", vec2(700, 0));
		Asset start_end_asset{"asset/jetpack_joyride/background/start/titleFG_2_TVOS.png"};
		start_end.add_component<Sprite>(start_end_asset, Sprite::Data{
															 .sorting_in_layer = 0,
															 .order_in_layer = 2,
															 .size = vec2(0, 800),
														 });

		GameObject hallway_begin = mgr.new_object("hallway_begin", "background", vec2(800, 0));
		Asset hallway_begin_asset{
			"asset/jetpack_joyride/background/hallway/hallway1FG_1_TVOS.png"};
		hallway_begin.add_component<Sprite>(hallway_begin_asset, Sprite::Data{
																	 .sorting_in_layer = 0,
																	 .order_in_layer = 1,
																	 .size = vec2(0, 800),
																 });

		GameObject hallway_middle
			= mgr.new_object("hallway_middle", "background", vec2(1400, 0));
		Asset hallway_middle_asset{
			"asset/jetpack_joyride/background/hallway/hallway1FG_2_TVOS.png"};
		hallway_middle.add_component<Sprite>(hallway_middle_asset, Sprite::Data{
																	   .sorting_in_layer = 0,
																	   .order_in_layer = 2,
																	   .size = vec2(0, 800),
																   });

		GameObject hallway_end = mgr.new_object("hallway_end", "background", vec2(2000, 0));
		Asset hallway_end_asset{
			"asset/jetpack_joyride/background/hallway/hallway1FG_1_TVOS.png"};
		hallway_end.add_component<Sprite>(hallway_end_asset, Sprite::Data{
																 .sorting_in_layer = 0,
																 .order_in_layer = 1,
																 .size = vec2(0, 800),
															 });

		GameObject forest_begin = mgr.new_object("forest_begin", "background", vec2(2600, 0));
		Asset forest_begin_asset{
			"asset/jetpack_joyride/background/forest/forestFG_1_TVOS.png"};
		forest_begin.add_component<Sprite>(forest_begin_asset, Sprite::Data{
																   .sorting_in_layer = 0,
																   .order_in_layer = 2,
																   .size = vec2(0, 800),
															   });

		GameObject forest_middle
			= mgr.new_object("forest_middle", "background", vec2(3400, 0));
		Asset forest_middle_asset{
			"asset/jetpack_joyride/background/forest/forestFG_3_TVOS.png"};
		forest_middle.add_component<Sprite>(forest_middle_asset, Sprite::Data{
																	 .sorting_in_layer = 0,
																	 .order_in_layer = 2,
																	 .size = vec2(0, 800),
																 });

		GameObject forest_end = mgr.new_object("forest_end", "background", vec2(4200, 0));
		Asset forest_end_asset{"asset/jetpack_joyride/background/forest/forestFG_2_TVOS.png"};
		forest_end.add_component<Sprite>(forest_end_asset, Sprite::Data{
															   .sorting_in_layer = 0,
															   .order_in_layer = 2,
															   .size = vec2(0, 800),
														   });

		GameObject forest_background_1
			= mgr.new_object("forest_background", "background", vec2(2600, 0));
		Asset forest_background_1_asset{
			"asset/jetpack_joyride/background/forest/forestBG1_1_TVOS.png"};
		forest_background_1.add_component<Sprite>(forest_background_1_asset,
												  Sprite::Data{
													  .sorting_in_layer = 0,
													  .order_in_layer = 0,
													  .size = vec2(0, 800),
												  });

		GameObject forest_background_2
			= mgr.new_object("forest_background", "background", vec2(3400, 0));
		Asset forest_background_2_asset{
			"asset/jetpack_joyride/background/forest/forestBG1_1_TVOS.png"};
		forest_background_2.add_component<Sprite>(forest_background_2_asset,
												  Sprite::Data{
													  .sorting_in_layer = 0,
													  .order_in_layer = 0,
													  .size = vec2(0, 800),
												  });

		GameObject forest_background_3
			= mgr.new_object("forest_background", "background", vec2(4200, 0));
		Asset forest_background_3_asset{
			"asset/jetpack_joyride/background/forest/forestBG1_1_TVOS.png"};
		forest_background_3.add_component<Sprite>(forest_background_3_asset,
												  Sprite::Data{
													  .sorting_in_layer = 0,
													  .order_in_layer = 0,
													  .size = vec2(0, 800),
												  });

		GameObject aquarium_begin
			= mgr.new_object("aquarium_begin", "background", vec2(4800, 0));
		Asset aquarium_begin_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_1_TVOS.png"};
		aquarium_begin.add_component<Sprite>(aquarium_begin_asset, Sprite::Data{
																	   .sorting_in_layer = 0,
																	   .order_in_layer = 1,
																	   .size = vec2(0, 800),
																   });

		GameObject aquarium_middle
			= mgr.new_object("aquarium_middle", "background", vec2(5400, 0));
		Asset aquarium_middle_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_3_TVOS.png"};
		aquarium_middle.add_component<Sprite>(aquarium_middle_asset, Sprite::Data{
																		 .sorting_in_layer = 0,
																		 .order_in_layer = 1,
																		 .size = vec2(0, 800),
																	 });

		GameObject aquarium_end = mgr.new_object("aquarium_end", "background", vec2(6000, 0));
		Asset aquarium_end_asset{
			"asset/jetpack_joyride/background/aquarium/glassTubeFG_2_TVOS.png"};
		aquarium_end.add_component<Sprite>(aquarium_end_asset, Sprite::Data{
																   .sorting_in_layer = 0,
																   .order_in_layer = 1,
																   .size = vec2(0, 800),
															   });
	}
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
