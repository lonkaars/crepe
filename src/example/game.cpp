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

class Scene1 : public Scene {
public:
	void load_scene() {
		Mediator & m = this->mediator;
		ComponentManager & mgr = m.component_manager;

		GameObject start_begin = mgr.new_object("start_begin", "background", vec2(0, 0));
		Asset start_begin_asset{"asset/jetpack_joyride/background/start/titleFG_1_TVOS.png"};
		start_begin.add_component<Sprite>(start_begin_asset, Sprite::Data{
																 .sorting_in_layer = 0,
																 .order_in_layer = 0,
																 .size = vec2(0, 800),
															 });

		GameObject start_end = mgr.new_object("start_end", "background", vec2(700, 0));
		Asset start_end_asset{"asset/jetpack_joyride/background/start/titleFG_2_TVOS.png"};
		start_end.add_component<Sprite>(start_end_asset, Sprite::Data{
															 .sorting_in_layer = 0,
															 .order_in_layer = 1,
															 .size = vec2(0, 800),
														 });

		GameObject hallway_begin = mgr.new_object("hallway_begin", "background", vec2(800, 0));
		Asset hallway_begin_asset{
			"asset/jetpack_joyride/background/hallway/hallway1FG_1_TVOS.png"};
		hallway_begin.add_component<Sprite>(hallway_begin_asset, Sprite::Data{
																	 .sorting_in_layer = 0,
																	 .order_in_layer = 0,
																	 .size = vec2(0, 800),
																 });

		GameObject camera = mgr.new_object("camera", "camera", vec2(600, 0));
		camera.add_component<Camera>(ivec2(1700, 720), vec2(2000, 800),
									 Camera::Data{
										 .bg_color = Color::RED,
									 });
		camera.add_component<Rigidbody>(Rigidbody::Data{
			.linear_velocity = vec2(1, 0),
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
