#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Sprite.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/system/RenderSystem.h>
#include <SDL2/SDL_timer.h>
#include <chrono>

using namespace crepe;

int main() {
	ComponentManager mgr;
	GameObject game_object1 = mgr.new_object("", "", vec2{0, 0}, 0, 1);
	GameObject game_object2 = mgr.new_object("", "", vec2{0, 0}, 0, 1);

	Texture img = Texture("asset/texture/test_ap43.png");
	game_object1.add_component<Sprite>(img, Color::MAGENTA, Sprite::FlipSettings{false, false}, 1, 1, 195);

	game_object2.add_component<Camera>(Color::WHITE, ivec2{1080, 720}, vec2{1036, 780}, 1.0f);

	RenderSystem sys{mgr};

	auto start = std::chrono::steady_clock::now();
	while (std::chrono::steady_clock::now() - start < std::chrono::seconds(5)) {
		sys.update();
		SDL_Delay(10);
	}

	return 0;
}
