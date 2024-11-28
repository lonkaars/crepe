#include <gtest/gtest.h>
#define protected public
#define private public
#include "api/EventManager.h"
#include "api/KeyCodes.h"
#include "system/InputSystem.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <crepe/ComponentManager.h>
#include <crepe/api/Button.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <gmock/gmock.h>

using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class InputTest : public ::testing::Test {
public:
	ComponentManager mgr{};
	InputSystem input_system{mgr}; // Initializes the InputSystem with the ComponentManager

	EventManager & event_manager = EventManager::get_instance();

protected:
	void SetUp() override { event_manager.clear(); }

	void simulate_mouse_click(int mouse_x, int mouse_y, Uint8 mouse_button) {
		SDL_Event event;

		// Simulate Mouse Button Down event
		SDL_zero(event);
		event.type = SDL_MOUSEBUTTONDOWN;
		event.button.x = mouse_x;
		event.button.y = mouse_y;
		event.button.button = mouse_button;
		SDL_PushEvent(&event);

		// Simulate Mouse Button Up event
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
	EventHandler<MousePressEvent> on_mouse_down = [&](const MousePressEvent & event) {
		mouse_triggered = true;
		EXPECT_EQ(event.mouse_x, 10);
		EXPECT_EQ(event.mouse_y, 10);
		EXPECT_EQ(event.button, MouseButton::LEFT_MOUSE);
		return false;
	};
	event_manager.subscribe<MousePressEvent>(on_mouse_down);

	SDL_Event event;
	SDL_zero(event);
	event.type = SDL_MOUSEBUTTONDOWN;
	event.button.x = 10;
	event.button.y = 10;
	event.button.button = SDL_BUTTON_LEFT;
	SDL_PushEvent(&event);

	input_system.update();
	event_manager.dispatch_events();
	EXPECT_TRUE(mouse_triggered);
}

TEST_F(InputTest, MouseUp) {
	bool function_triggered = false;
	EventHandler<MouseReleaseEvent> on_mouse_release = [&](const MouseReleaseEvent & e) {
		function_triggered = true;
		EXPECT_EQ(e.mouse_x, 10);
		EXPECT_EQ(e.mouse_y, 10);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false;
	};
	event_manager.subscribe<MouseReleaseEvent>(on_mouse_release);

	SDL_Event event;
	SDL_zero(event);
	event.type = SDL_MOUSEBUTTONUP;
	event.button.x = 10;
	event.button.y = 10;
	event.button.button = SDL_BUTTON_LEFT;
	SDL_PushEvent(&event);

	input_system.update();
	event_manager.dispatch_events();
	EXPECT_TRUE(function_triggered);
}

TEST_F(InputTest, MouseMove) {
	bool function_triggered = false;
	EventHandler<MouseMoveEvent> on_mouse_move = [&](const MouseMoveEvent & e) {
		function_triggered = true;
		EXPECT_EQ(e.mouse_x, 10);
		EXPECT_EQ(e.mouse_y, 10);
		EXPECT_EQ(e.rel_x, 10);
		EXPECT_EQ(e.rel_y, 10);
		return false;
	};
	event_manager.subscribe<MouseMoveEvent>(on_mouse_move);

	SDL_Event event;
	SDL_zero(event);
	event.type = SDL_MOUSEMOTION;
	event.motion.x = 10;
	event.motion.y = 10;
	event.motion.xrel = 10;
	event.motion.yrel = 10;
	SDL_PushEvent(&event);

	input_system.update();
	event_manager.dispatch_events();
	EXPECT_TRUE(function_triggered);
}

TEST_F(InputTest, KeyDown) {
	bool function_triggered = false;

	// Define event handler for KeyPressEvent
	EventHandler<KeyPressEvent> on_key_press = [&](const KeyPressEvent & event) {
		function_triggered = true;
		EXPECT_EQ(event.key, Keycode::B); // Validate the key is 'B'
		EXPECT_EQ(event.repeat, true); // Validate repeat flag
		return false;
	};

	event_manager.subscribe<KeyPressEvent>(on_key_press);

	// Simulate SDL_KEYDOWN event
	SDL_Event test_event;
	SDL_zero(test_event);
	test_event.type = SDL_KEYDOWN; // Key down event
	test_event.key.keysym.scancode = SDL_SCANCODE_B; // Set scancode for 'B'
	test_event.key.repeat = 1; // Set repeat flag
	SDL_PushEvent(&test_event);

	input_system.update(); // Process the event
	event_manager.dispatch_events(); // Dispatch events to handlers

	EXPECT_TRUE(function_triggered); // Check if the handler was triggered
}

TEST_F(InputTest, KeyUp) {
	bool function_triggered = false;
	EventHandler<KeyReleaseEvent> on_key_release = [&](const KeyReleaseEvent & event) {
		function_triggered = true;
		EXPECT_EQ(event.key, Keycode::B);
		return false;
	};
	event_manager.subscribe<KeyReleaseEvent>(on_key_release);

	SDL_Event event;
	SDL_zero(event);
	event.type = SDL_KEYUP;
	event.key.keysym.scancode = SDL_SCANCODE_B;
	SDL_PushEvent(&event);

	input_system.update();
	event_manager.dispatch_events();
	EXPECT_TRUE(function_triggered);
}

TEST_F(InputTest, MouseClick) {
	bool on_click_triggered = false;
	EventHandler<MouseClickEvent> on_mouse_click = [&](const MouseClickEvent & event) {
		on_click_triggered = true;
		EXPECT_EQ(event.button, MouseButton::LEFT_MOUSE);
		EXPECT_EQ(event.mouse_x, 10);
		EXPECT_EQ(event.mouse_y, 10);
		return false;
	};
	event_manager.subscribe<MouseClickEvent>(on_mouse_click);

	this->simulate_mouse_click(10, 10, SDL_BUTTON_LEFT);
	input_system.update();
	event_manager.dispatch_events();
	EXPECT_TRUE(on_click_triggered);
}

TEST_F(InputTest, testButtonClick) {
	GameObject obj = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	bool button_clicked = false;
	std::function<void()> on_click = [&]() { button_clicked = true; };
	auto & button = obj.add_component<Button>(100, 100,on_click,false);
	
	bool hover = false;
	button.active = true;
	
	button.is_pressed = false;
	button.is_toggle = false;
	this->simulate_mouse_click(101, 101, SDL_BUTTON_LEFT);
	input_system.update();
	event_manager.dispatch_events();
	EXPECT_FALSE(button_clicked);

	this->simulate_mouse_click(10, 10, SDL_BUTTON_LEFT);
	input_system.update();
	event_manager.dispatch_events();
	EXPECT_TRUE(button_clicked);
}

TEST_F(InputTest, testButtonHover) {
	GameObject obj = mgr.new_object("body", "person", vec2{0, 0}, 0, 1);
	bool button_clicked = false;
	std::function<void()> on_click = [&]() { button_clicked = true; };
	auto & button = obj.add_component<Button>(100, 100,on_click,false);
	button.active = true;
	button.width = 100;
	button.height = 100;
	button.is_pressed = false;
	button.is_toggle = false;

	// Mouse not on button
	SDL_Event event;
	SDL_zero(event);
	event.type = SDL_MOUSEMOTION;
	event.motion.x = 200;
	event.motion.y = 200;
	event.motion.xrel = 10;
	event.motion.yrel = 10;
	SDL_PushEvent(&event);

	input_system.update();
	event_manager.dispatch_events();
	EXPECT_FALSE(button.hover);

	// Mouse on button
	SDL_Event hover_event;
	SDL_zero(hover_event);
	hover_event.type = SDL_MOUSEMOTION;
	hover_event.motion.x = 10;
	hover_event.motion.y = 10;
	hover_event.motion.xrel = 10;
	hover_event.motion.yrel = 10;
	SDL_PushEvent(&hover_event);

	input_system.update();
	event_manager.dispatch_events();
	EXPECT_TRUE(button.hover);
}
