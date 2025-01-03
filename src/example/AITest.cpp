#include <crepe/api/AI.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/manager/Mediator.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

class Script1 : public Script {
	bool shutdown(const ShutDownEvent & event) {
		// Very dirty way of shutting down the game
		throw "ShutDownEvent";
		return true;
	}

	bool mousemove(const MouseMoveEvent & event) {
		/*RefVector<AI> aivec = this->get_components<AI>();
		AI & ai = aivec.front().get();
		ai.flee_target
			= vec2{static_cast<float>(event.mouse_x), static_cast<float>(event.mouse_y)};*/
		return true;
	}

	void init() {
		subscribe<ShutDownEvent>([this](const ShutDownEvent & ev) -> bool {
			return this->shutdown(ev);
		});
		subscribe<MouseMoveEvent>([this](const MouseMoveEvent & ev) -> bool {
			return this->mousemove(ev);
		});
	}
};

class Scene1 : public Scene {
public:
	void load_scene() override {
		Mediator & mediator = this->mediator;
		ComponentManager & mgr = mediator.component_manager;

		GameObject game_object1 = mgr.new_object("", "", vec2 {0, 0}, 0, 1);
		GameObject game_object2 = mgr.new_object("", "", vec2 {0, 0}, 0, 1);

		Asset img {"asset/texture/test_ap43.png"};

		Sprite & test_sprite = game_object1.add_component<Sprite>(
			img,
			Sprite::Data {
				.color = Color::MAGENTA,
				.flip = Sprite::FlipSettings {false, false},
				.sorting_in_layer = 2,
				.order_in_layer = 2,
				.size = {0, 100},
				.angle_offset = 0,
				.position_offset = {0, 0},
			}
		);

		AI & ai = game_object1.add_component<AI>(3000);
		// ai.arrive_on();
		// ai.flee_on();
		ai.path_follow_on();
		ai.make_oval_path(500, 1000, {0, -1000}, 1.5708, true);
		ai.make_oval_path(1000, 500, {0, 500}, 4.7124, false);
		game_object1.add_component<Rigidbody>(Rigidbody::Data {
			.mass = 0.1f,
			.max_linear_velocity = 40,
		});
		game_object1.add_component<BehaviorScript>().set_script<Script1>();

		game_object2.add_component<Camera>(
			ivec2 {1080, 720}, vec2 {5000, 5000},
			Camera::Data {
				.bg_color = Color::WHITE,
				.zoom = 1,
			}
		);
	}

	string get_name() const override { return "Scene1"; }
};

int main() {
	LoopManager engine;
	engine.add_scene<Scene1>();
	engine.start();

	return 0;
}
