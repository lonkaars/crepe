#include <crepe/api/Camera.h>
#include <crepe/ComponentManager.h>
#include <crepe/Component.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/api/EventManager.h>
#include <crepe/system/InputSystem.h>
#include <crepe/system/AnimatorSystem.h>
#include <crepe/api/Button.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Texture.h>
#include <SDL2/SDL_timer.h>
#include <crepe/types.h>
#include <chrono>
#include <iostream>
using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	ComponentManager mgr;
	RenderSystem sys{mgr};
	EventManager& event_mgr = EventManager::get_instance();
	InputSystem input_sys{mgr};
	AnimatorSystem asys{mgr};
	GameObject camera_obj = mgr.new_object("", "", vec2{0, 0}, 0, 1);
	camera_obj.add_component<Camera>(Color::WHITE, ivec2{1080, 720}, vec2{2000, 2000}, 1.0f);

	GameObject button_obj = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	auto s2 = Texture("asset/texture/test_ap43.png");
	bool button_clicked = false;
	auto & sprite2 = button_obj.add_component<Sprite>(
			s2, Color::GREEN, Sprite::FlipSettings{false, false}, 2, 1, 100);
	std::function<void()> on_click = [&]() { 
		std::cout << "button clicked" << std::endl;
	};
	auto & button = button_obj.add_component<Button>(100, 100, on_click, false);
	button.active = true;
	auto start = std::chrono::steady_clock::now();
	while (true) {
		input_sys.update();
		sys.update();
		asys.update();
		event_mgr.dispatch_events();
		SDL_Delay(30);
	}
	return 0;
}
