#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "system/InputSystem.h"
#include "api/EventManager.h"
#include "api/KeyCodes.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class InputTest : public ::testing::Test {
public:
InputSystem input_system;
EventManager& event_manager = EventManager::get_instance();
protected:
	void SetUp() override {
	}

	void TearDown() override {
		
	}
void simulate_mouse_click(int mouse_x, int mouse_y, Uint8 mouse_button) {
    SDL_Event event;

    // Simulate Mouse Button Down event
    SDL_zero(event);
    event.type = SDL_MOUSEBUTTONDOWN;
    event.button.x = mouse_x;
    event.button.y = mouse_y;
    event.button.button = mouse_button;
    SDL_PushEvent(&event);
    SDL_zero(event);
    event.type = SDL_MOUSEBUTTONUP;
    event.button.x = mouse_x;
    event.button.y = mouse_y;
    event.button.button = mouse_button;
    SDL_PushEvent(&event);
}

};

TEST_F(InputTest, KeyDown) {

	SDL_Event event;
	SDL_zero(event);
    event.type = SDL_MOUSEBUTTONDOWN;
    event.button.x = 10;
    event.button.y = 10;
    event.button.button = mouse_bu;
    SDL_PushEvent(&event);  // Push event into the SDL event queue
}
