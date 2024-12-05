#include <crepe/manager/Mediator.h>
#include <SDL2/SDL_timer.h>
#include <chrono>
#include <crepe/manager/ComponentManager.h>
#include <crepe/api/AI.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>

using namespace crepe;
using namespace std;

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
		game_object1.add_component<AI>(1, 200, 200).seek_on();

		game_object2.add_component<Camera>(Color::WHITE, ivec2{1080, 720}, vec2{1036, 780},
										   1.0f);
	}

	string get_name() const override { return "Scene1"; }
};

int main() {
	LoopManager engine;
	engine.add_scene<Scene1>();
	engine.start();

	return 0;
}
