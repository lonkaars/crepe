#include <gtest/gtest.h>
#define protected public
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include "system/InputSystem.h"
#include <crepe/ComponentManager.h>
#include "api/EventManager.h"
#include "api/KeyCodes.h"
#include <gmock/gmock.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <crepe/api/Button.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class InputTest : public ::testing::Test {
public:
ComponentManager mgr{};
InputSystem input_system{mgr};

EventManager& event_manager = EventManager::get_instance();
protected:
	void SetUp() override {
		event_manager.clear();
	}

	void TearDown() override {
		event_manager.clear();
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

TEST_F(InputTest, MouseDown) {
	bool mouse_triggered = false;
	EventHandler<MousePressEvent> on_mouse_click = [&](const MousePressEvent& event) {
        // Handle the mouse click event here
		mouse_triggered = true;
        EXPECT_EQ(event.mouse_x, 10);
        EXPECT_EQ(event.mouse_y, 10);
        EXPECT_EQ(event.button, MouseButton::LEFT_MOUSE);
		return false;
    };
	event_manager.subscribe<MousePressEvent>(on_mouse_click);
	SDL_Event event;
	SDL_zero(event);
    event.type = SDL_MOUSEBUTTONDOWN;
    event.button.x = 10;
    event.button.y = 10;
    event.button.button = SDL_BUTTON_LEFT;
    SDL_PushEvent(&event);
	EXPECT_TRUE(mouse_triggered);
}

TEST_F(InputTest, MouseUp) {
	 EventHandler<MouseReleaseEvent> on_mouse_click = [&](const MouseReleaseEvent& event) {
        // Handle the mouse click event here
        EXPECT_EQ(event.mouse_x, 10);
        EXPECT_EQ(event.mouse_y, 10);
        EXPECT_EQ(event.button, MouseButton::LEFT_MOUSE);
		return false;
    };
	event_manager.subscribe<MouseReleaseEvent>(on_mouse_click);
	SDL_Event event;
	SDL_zero(event);
    event.type = SDL_MOUSEBUTTONUP;
    event.button.x = 10;
    event.button.y = 10;
    event.button.button = SDL_BUTTON_LEFT;
    SDL_PushEvent(&event);
}
TEST_F(InputTest, MouseUp) {
	 EventHandler<MouseReleaseEvent> on_mouse_click = [&](const MouseReleaseEvent& event) {
        // Handle the mouse click event here
        EXPECT_EQ(event.mouse_x, 10);
        EXPECT_EQ(event.mouse_y, 10);
        EXPECT_EQ(event.button, MouseButton::LEFT_MOUSE);
		return false;
    };
	event_manager.subscribe<MouseReleaseEvent>(on_mouse_click);
	SDL_Event event;
	SDL_zero(event);
    event.type = SDL_MOUSEBUTTONUP;
    event.button.x = 10;
    event.button.y = 10;
    event.button.button = SDL_BUTTON_LEFT;
    SDL_PushEvent(&event);
}
TEST_F(InputTest, KeyDown) {
	 EventHandler<KeyPressEvent> on_mouse_click = [&](const KeyPressEvent& event) {
        // Handle the mouse click event here
        EXPECT_EQ(event.key, Keycode::B);
		EXPECT_EQ(event.repeat, true);
		return false;
    };
	event_manager.subscribe<KeyPressEvent>(on_mouse_click);
	SDL_Event event;
	SDL_zero(event);
    event.type = SDL_KEYUP;
    event.button.button = SDL_BUTTON_LEFT;
	event.key.repeat = 1;
    SDL_PushEvent(&event);
}
TEST_F(InputTest, KeyUp) {
	 EventHandler<KeyReleaseEvent> on_mouse_click = [&](const KeyReleaseEvent& event) {
        // Handle the mouse click event here
        EXPECT_EQ(event.key, Keycode::B);
		return false;
    };
	event_manager.subscribe<KeyReleaseEvent>(on_mouse_click);
	SDL_Event event;
	SDL_zero(event);
    event.type = SDL_KEYUP;
    event.button.button = SDL_BUTTON_LEFT;
    SDL_PushEvent(&event);
}
TEST_F(InputTest, KeyClick) {
	GameObject obj = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	Button test_button;
	bool button_clicked = false;
	test_button.active = true;
	test_button.width = 100;
	test_button.height = 100;
	std::function<void()> on_click = [&]() {
        button_clicked = true;
    };
	test_button.on_click = on_click;
	test_button.is_pressed = false;
	test_button.is_toggle = false;
	obj.add_component<Button>();
	EventHandler<KeyReleaseEvent> on_mouse_click = [&](const KeyReleaseEvent& event) {
        EXPECT_EQ(event.key, Keycode::B);
		return false;
    };
	event_manager.subscribe<KeyReleaseEvent>(on_mouse_click);
	SDL_Event event;
	SDL_zero(event);
    event.type = SDL_KEYUP;
    event.button.button = SDL_BUTTON_LEFT;
    SDL_PushEvent(&event);
}
TEST_F(InputTest, testButton) {
	GameObject obj = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	Button test_button;
	bool button_clicked = false;
	test_button.active = true;
	test_button.width = 100;
	test_button.height = 100;
	std::function<void()> on_click = [&]() {
        button_clicked = true;
    };
	test_button.on_click = on_click;
	test_button.is_pressed = false;
	test_button.is_toggle = false;
	obj.add_component<Button>();
	this->simulate_mouse_click(10,10,MouseButton::LEFT_MOUSE);
}
