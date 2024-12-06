#include <SDL2/SDL_timer.h>
#include <chrono>
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
#include <crepe/api/Texture.h>
#include <crepe/manager/Mediator.h>

using namespace crepe;
using namespace std;

class Script1 : public Script {
	bool shutdown(const ShutDownEvent & event) {
		// Very dirty way of shutting down the game
		throw "ShutDownEvent";
		return true;
	}

	void init() {
		subscribe<ShutDownEvent>(
			[this](const ShutDownEvent & ev) -> bool { return this->shutdown(ev); });
	}
};

class Scene1 : public Scene {
public:
	void load_scene() override {
		Mediator & mediator = this->mediator;
		ComponentManager & mgr = mediator.component_manager;

		GameObject game_object1 = mgr.new_object("", "", vec2{250, 250}, 0, 1);
		GameObject game_object2 = mgr.new_object("", "", vec2{0, 0}, 0, 1);

		Texture img = Texture("asset/texture/test_ap43.png");
		game_object1.add_component<Sprite>(img, Color::MAGENTA,
										   Sprite::FlipSettings{false, false}, 1, 1, 195);
		game_object1.add_component<AI>(200).seek_on();
		game_object1.add_component<Rigidbody>(Rigidbody::Data{
			.mass = 1.0f, .max_linear_velocity = {21, 21}, // sqrt(21^2 + 21^2) = 30
		});

		game_object2.add_component<Camera>(Color::WHITE, ivec2{1080, 720}, vec2{1036, 780},
										   1.0f);
		game_object2.add_component<BehaviorScript>().set_script<Script1>();
	}

	string get_name() const override { return "Scene1"; }
};

int main() {
	LoopManager engine;
	engine.add_scene<Scene1>();
	engine.start();

	return 0;
}
