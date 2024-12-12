#include <crepe/api/Event.h>
#include <crepe/manager/EventManager.h>
#include <crepe/manager/Mediator.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
using namespace std;
using namespace std::chrono_literals;
using namespace crepe;

class EventManagerTest : public ::testing::Test {
protected:
	Mediator mediator;
	EventManager event_mgr{mediator};
	void SetUp() override {
		// Clear any existing subscriptions or events before each test
		event_mgr.clear();
	}

	void TearDown() override {
		// Ensure cleanup after each test
		event_mgr.clear();
	}
};
TEST_F(EventManagerTest, EventSubscription) {
	EventHandler<KeyPressEvent> key_handler = [](const KeyPressEvent & e) { return true; };

	// Subscribe to KeyPressEvent
	event_mgr.subscribe<KeyPressEvent>(key_handler, 1);

	// Verify subscription (not directly verifiable; test by triggering event)

	event_mgr.trigger_event<KeyPressEvent>(
		KeyPressEvent{
			.repeat = true,
			.key = Keycode::A,
		},
		1);
	event_mgr.trigger_event<KeyPressEvent>(
		KeyPressEvent{
			.repeat = true,
			.key = Keycode::A,

		},
		EventManager::CHANNEL_ALL);
}
TEST_F(EventManagerTest, EventManagerTest_trigger_all_channels) {
	bool triggered = false;

	EventHandler<MouseClickEvent> mouse_handler = [&](const MouseClickEvent & e) {
		triggered = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false;
	};
	event_mgr.subscribe<MouseClickEvent>(mouse_handler, EventManager::CHANNEL_ALL);

	MouseClickEvent click_event{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE};
	event_mgr.trigger_event<MouseClickEvent>(click_event,
																EventManager::CHANNEL_ALL);

	EXPECT_TRUE(triggered);
}
TEST_F(EventManagerTest, EventManagerTest_trigger_one_channel) {
	bool triggered = false;
	int test_channel = 1;
	EventHandler<MouseClickEvent> mouse_handler = [&](const MouseClickEvent & e) {
		triggered = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false;
	};
	event_mgr.subscribe<MouseClickEvent>(mouse_handler, test_channel);

	MouseClickEvent click_event{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE};
	event_mgr.trigger_event<MouseClickEvent>(click_event,
																EventManager::CHANNEL_ALL);

	EXPECT_FALSE(triggered);
	event_mgr.trigger_event<MouseClickEvent>(click_event, test_channel);
}

TEST_F(EventManagerTest, EventManagerTest_callback_propagation) {

	// Flags to track handler calls
	bool triggered_true = false;
	bool triggered_false = false;

	// Handlers
	EventHandler<MouseClickEvent> mouse_handler_true = [&](const MouseClickEvent & e) {
		triggered_true = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return true; // Stops propagation
	};

	EventHandler<MouseClickEvent> mouse_handler_false = [&](const MouseClickEvent & e) {
		triggered_false = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false; // Allows propagation
	};

	// Test event
	MouseClickEvent click_event{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE};
	event_mgr.subscribe<MouseClickEvent>(mouse_handler_true, EventManager::CHANNEL_ALL);
	event_mgr.subscribe<MouseClickEvent>(mouse_handler_false, EventManager::CHANNEL_ALL);

	// Trigger event
	event_mgr.trigger_event<MouseClickEvent>(click_event, EventManager::CHANNEL_ALL);

	// Check that only the true handler was triggered
	EXPECT_TRUE(triggered_true);
	EXPECT_FALSE(triggered_false);

	// Reset and clear
	triggered_true = false;
	triggered_false = false;
	event_mgr.clear();
	event_mgr.subscribe<MouseClickEvent>(mouse_handler_false, EventManager::CHANNEL_ALL);
	event_mgr.subscribe<MouseClickEvent>(mouse_handler_true, EventManager::CHANNEL_ALL);

	// Trigger event again
	event_mgr.trigger_event<MouseClickEvent>(click_event, EventManager::CHANNEL_ALL);

	// Check that both handlers were triggered
	EXPECT_TRUE(triggered_true);
	EXPECT_TRUE(triggered_false);
}

TEST_F(EventManagerTest, EventManagerTest_queue_dispatch) {
	bool triggered1 = false;
	bool triggered2 = false;
	int test_channel = 1;
	EventHandler<MouseClickEvent> mouse_handler1 = [&](const MouseClickEvent & e) {
		triggered1 = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false; // Allows propagation
	};
	EventHandler<MouseClickEvent> mouse_handler2 = [&](const MouseClickEvent & e) {
		triggered2 = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false; // Allows propagation
	};
	event_mgr.subscribe<MouseClickEvent>(mouse_handler1);
	event_mgr.subscribe<MouseClickEvent>(mouse_handler2, test_channel);

	event_mgr.queue_event<MouseClickEvent>(
		MouseClickEvent{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE});
	event_mgr.queue_event<MouseClickEvent>(
		MouseClickEvent{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE},
		test_channel);
	event_mgr.dispatch_events();
	EXPECT_TRUE(triggered1);
	EXPECT_TRUE(triggered2);
}

TEST_F(EventManagerTest, EventManagerTest_unsubscribe) {

	// Flags to track if handlers are triggered
	bool triggered1 = false;
	bool triggered2 = false;

	// Define EventHandlers
	EventHandler<MouseClickEvent> mouse_handler1 = [&](const MouseClickEvent & e) {
		triggered1 = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false; // Allows propagation
	};

	EventHandler<MouseClickEvent> mouse_handler2 = [&](const MouseClickEvent & e) {
		triggered2 = true;
		EXPECT_EQ(e.mouse_pos.x, 100);
		EXPECT_EQ(e.mouse_pos.y, 200);
		EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
		return false; // Allows propagation
	};
	// Subscribe handlers
	subscription_t handler1_id = event_mgr.subscribe<MouseClickEvent>(mouse_handler1);
	subscription_t handler2_id = event_mgr.subscribe<MouseClickEvent>(mouse_handler2);

	// Queue events
	event_mgr.queue_event<MouseClickEvent>(
		MouseClickEvent{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE});

	// Dispatch events - both handlers should be triggered
	event_mgr.dispatch_events();
	EXPECT_TRUE(triggered1); // Handler 1 should be triggered
	EXPECT_TRUE(triggered2); // Handler 2 should be triggered

	// Reset flags
	triggered1 = false;
	triggered2 = false;

	// Unsubscribe handler1
	event_mgr.unsubscribe(handler1_id);

	// Queue the same event again
	event_mgr.queue_event<MouseClickEvent>(
		MouseClickEvent{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE});

	// Dispatch events - only handler 2 should be triggered, handler 1 should NOT
	event_mgr.dispatch_events();
	EXPECT_FALSE(triggered1); // Handler 1 should NOT be triggered
	EXPECT_TRUE(triggered2); // Handler 2 should be triggered

	// Reset flags
	triggered2 = false;

	// Unsubscribe handler2
	event_mgr.unsubscribe(handler2_id);

	// Queue the event again
	event_mgr.queue_event<MouseClickEvent>(
		MouseClickEvent{.mouse_pos = {100, 200}, .button = MouseButton::LEFT_MOUSE});

	// Dispatch events - no handler should be triggered
	event_mgr.dispatch_events();
	EXPECT_FALSE(triggered1); // Handler 1 should NOT be triggered
	EXPECT_FALSE(triggered2); // Handler 2 should NOT be triggered
}
