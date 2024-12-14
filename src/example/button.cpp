#include <SDL2/SDL_timer.h>
#include <chrono>
#include <crepe/Component.h>
#include <crepe/api/Animator.h>
#include <crepe/api/Button.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Texture.h>
#include <crepe/api/Transform.h>
#include <crepe/facade/SDLContext.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/EventManager.h>
#include <crepe/system/AnimatorSystem.h>
#include <crepe/system/InputSystem.h>
#include <crepe/system/RenderSystem.h>
#include <crepe/types.h>
using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	Mediator mediator;
	ComponentManager mgr{mediator};
	RenderSystem sys{mediator};
	EventManager event_mgr{mediator};
	InputSystem input_sys{mediator};
	SDLContext sdl_context{mediator};
	GameObject obj = mgr.new_object("camera", "camera", vec2{0, 0}, 0, 1);
	auto & camera = obj.add_component<Camera>(
		ivec2{500, 500}, vec2{500, 500}, Camera::Data{.bg_color = Color::WHITE, .zoom = 1.0f});
	auto start = std::chrono::steady_clock::now();
	while (true) {
		const keyboard_state_t & keyboard_state = sdl_context.get_keyboard_state();
		input_sys.update();
		sys.update();
		event_mgr.dispatch_events();
		SDL_Delay(30);
	}
	return 0;
}
