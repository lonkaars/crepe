
#include "api/EventManager.h"
#include "api/Event.h"
#include "api/IKeyListener.h"
#include "api/IMouseListener.h"
#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;
using namespace std::chrono_literals;
using namespace crepe;


class EventManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear any existing subscriptions or events before each test
        EventManager::get_instance().clear();
    }

    void TearDown() override {
        // Ensure cleanup after each test
        EventManager::get_instance().clear();
    }
};
class MockKeyListener : public IKeyListener {
public:
    MOCK_METHOD(bool, on_key_pressed, (const KeyPressEvent& event), (override));
    MOCK_METHOD(bool, on_key_released, (const KeyReleaseEvent& event), (override));
};

class MockMouseListener : public IMouseListener {
public:
    MOCK_METHOD(bool, on_mouse_clicked, (const MouseClickEvent& event), (override));
    MOCK_METHOD(bool, on_mouse_pressed, (const MousePressEvent& event), (override));
    MOCK_METHOD(bool, on_mouse_released, (const MouseReleaseEvent& event), (override));
    MOCK_METHOD(bool, on_mouse_moved, (const MouseMoveEvent& event), (override));
};
TEST_F(EventManagerTest, EventSubscription) {
    EventHandler<KeyPressEvent> key_handler = [](const KeyPressEvent& e) {
        std::cout << "Key Event Triggered" << std::endl;
        return true;
    };

    // Subscribe to KeyPressEvent
    EventManager::get_instance().subscribe<KeyPressEvent>(key_handler, 1);

    // Verify subscription (not directly verifiable; test by triggering event)
    
    EventManager::get_instance().trigger_event<KeyPressEvent>(KeyPressEvent{
		.repeat = true,
		.key = Keycode::A,
	}, 1);
	EventManager::get_instance().trigger_event<KeyPressEvent>(KeyPressEvent{
		.repeat = true,
		.key = Keycode::A,
		
	}, CHANNEL_ALL);
	
}
TEST_F(EventManagerTest, EventManagerTest_trigger_all_channels) {
    bool triggered = false;

	EventHandler<MouseClickEvent> mouse_handler = [&](const MouseClickEvent& e) {
        triggered = true;
		std::cout << "mouse handled" <<std::endl;
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;
    };
    EventManager::get_instance().subscribe<MouseClickEvent>(mouse_handler, CHANNEL_ALL);

    MouseClickEvent click_event{
		.mouse_x = 100,
		.mouse_y = 200,
		.button = MouseButton::LEFT_MOUSE
	};
	EventManager::get_instance().trigger_event<MouseClickEvent>(click_event, CHANNEL_ALL);

    EXPECT_TRUE(triggered);
}

TEST_F(EventManagerTest, EventManagerTest_priority_order) {
    EventManager& event_manager = EventManager::get_instance();

    // Vector to track call order
    std::vector<int> call_order;

    // Handlers with different priorities
    EventHandler<MouseClickEvent> handler_priority_3 = [&](const MouseClickEvent& e) {
        call_order.push_back(3);
        return false;  // Allow propagation
    };

    EventHandler<MouseClickEvent> handler_priority_1 = [&](const MouseClickEvent& e) {
        call_order.push_back(1);
        return false;  // Allow propagation
    };

    EventHandler<MouseClickEvent> handler_priority_2 = [&](const MouseClickEvent& e) {
        call_order.push_back(2);
        return false;  // Allow propagation
    };

    // Subscribe handlers with different priorities
    event_manager.subscribe<MouseClickEvent>(handler_priority_1, CHANNEL_ALL, 1);
    event_manager.subscribe<MouseClickEvent>(handler_priority_3, CHANNEL_ALL, 3);
	event_manager.subscribe<MouseClickEvent>(handler_priority_2, CHANNEL_ALL, 2);

    // Trigger the event
    event_manager.trigger_event<MouseClickEvent>(MouseClickEvent{
        .mouse_x = 100,
        .mouse_y = 200,
        .button = MouseButton::LEFT_MOUSE
    }, CHANNEL_ALL);

    // Check the call order matches the expected priority order
    std::vector<int> expected_order = {3, 2, 1};
    EXPECT_EQ(call_order, expected_order);

}

TEST_F(EventManagerTest, EventManagerTest_callback_propagation) {
    EventManager& event_manager = EventManager::get_instance();

    // Flags to track handler calls
    bool triggered_true = false;
    bool triggered_false = false;

    // Handlers
    EventHandler<MouseClickEvent> mouse_handler_true = [&](const MouseClickEvent& e) {
        triggered_true = true;
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return true;  // Stops propagation
    };

    EventHandler<MouseClickEvent> mouse_handler_false = [&](const MouseClickEvent& e) {
        triggered_false = true;
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };

    // Test event
    MouseClickEvent click_event{
        .mouse_x = 100,
        .mouse_y = 200,
        .button = MouseButton::LEFT_MOUSE
    };

    // First Scenario: True handler has higher priority
    event_manager.subscribe<MouseClickEvent>(mouse_handler_true, CHANNEL_ALL, 1);
    event_manager.subscribe<MouseClickEvent>(mouse_handler_false, CHANNEL_ALL, 0);

    // Trigger event
    event_manager.trigger_event<MouseClickEvent>(click_event, CHANNEL_ALL);

    // Check that only the true handler was triggered
    EXPECT_TRUE(triggered_true);
    EXPECT_FALSE(triggered_false);

    // Reset and clear
    triggered_true = false;
    triggered_false = false;
    event_manager.clear();

    // Second Scenario: False handler has higher priority
    event_manager.subscribe<MouseClickEvent>(mouse_handler_true, CHANNEL_ALL, 0);
    event_manager.subscribe<MouseClickEvent>(mouse_handler_false, CHANNEL_ALL, 1);

    // Trigger event again
    event_manager.trigger_event<MouseClickEvent>(click_event, CHANNEL_ALL);

    // Check that both handlers were triggered
    EXPECT_TRUE(triggered_true);
    EXPECT_TRUE(triggered_false);
}

TEST_F(EventManagerTest, EventManagerTest_queue_dispatch) {
	EventManager& event_manager = EventManager::get_instance();
	bool triggered1 = false;
	bool triggered2 = false;
	int test_channel = 1;
	EventHandler<MouseClickEvent> mouse_handler1 = [&](const MouseClickEvent& e) {
        triggered1 = true;
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };
	EventHandler<MouseClickEvent> mouse_handler2 = [&](const MouseClickEvent& e) {
        triggered2 = true;
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };
	event_manager.subscribe<MouseClickEvent>(mouse_handler1);
	event_manager.subscribe<MouseClickEvent>(mouse_handler2,test_channel);
	
	event_manager.queue_event<MouseClickEvent>(MouseClickEvent{
		.mouse_x = 100,
		.mouse_y = 200,
		.button = MouseButton::LEFT_MOUSE
	});
	event_manager.queue_event<MouseClickEvent>(MouseClickEvent{
		.mouse_x = 100,
		.mouse_y = 200,
		.button = MouseButton::LEFT_MOUSE
	},test_channel);
	event_manager.dispatch_events();
	EXPECT_TRUE(triggered1);
	EXPECT_TRUE(triggered2);
}

TEST_F(EventManagerTest, EventManagerTest_dispatch_priority) {
	EventManager& event_manager = EventManager::get_instance();
	std::vector<int> call_order;
	int test_channel = 1;
	EventHandler<MouseClickEvent> mouse_handler1 = [&](const MouseClickEvent& e) {
		call_order.push_back(1);
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };
	EventHandler<MouseClickEvent> mouse_handler2 = [&](const MouseClickEvent& e) {
        call_order.push_back(2);
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };
	EventHandler<MouseClickEvent> mouse_handler3 = [&](const MouseClickEvent& e) {
        call_order.push_back(3);
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };
	event_manager.subscribe<MouseClickEvent>(mouse_handler2,CHANNEL_ALL,2);
	event_manager.subscribe<MouseClickEvent>(mouse_handler1,CHANNEL_ALL,1);
	event_manager.subscribe<MouseClickEvent>(mouse_handler3,CHANNEL_ALL,3);
	event_manager.queue_event<MouseClickEvent>(MouseClickEvent{
		.mouse_x = 100,
		.mouse_y = 200,
		.button = MouseButton::LEFT_MOUSE
	});
	event_manager.dispatch_events();
	std::vector<int> expected_order = {3, 2, 1};
    EXPECT_EQ(call_order, expected_order);
}

TEST_F(EventManagerTest, EventManagerTest_unsubscribe) {
    EventManager& event_manager = EventManager::get_instance();
    
    // Flags to track if handlers are triggered
    bool triggered1 = false;
    bool triggered2 = false;
    
    // Define EventHandlers
    EventHandler<MouseClickEvent> mouse_handler1 = [&](const MouseClickEvent& e) {
        triggered1 = true;
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };

    EventHandler<MouseClickEvent> mouse_handler2 = [&](const MouseClickEvent& e) {
        triggered2 = true;
        EXPECT_EQ(e.mouse_x, 100);
        EXPECT_EQ(e.mouse_y, 200);
        EXPECT_EQ(e.button, MouseButton::LEFT_MOUSE);
        return false;  // Allows propagation
    };
    // Subscribe handlers
    event_manager.subscribe<MouseClickEvent>(mouse_handler1);
    event_manager.subscribe<MouseClickEvent>(mouse_handler2);
    
    // Queue events
    event_manager.queue_event<MouseClickEvent>(MouseClickEvent{
        .mouse_x = 100,
        .mouse_y = 200,
        .button = MouseButton::LEFT_MOUSE
    });
    
    // Dispatch events - both handlers should be triggered
    event_manager.dispatch_events();
    EXPECT_TRUE(triggered1);  // Handler 1 should be triggered
    EXPECT_TRUE(triggered2);  // Handler 2 should be triggered
    
    // Reset flags
    triggered1 = false;
    triggered2 = false;
    
    // Unsubscribe handler1
    event_manager.unsubscribe<MouseClickEvent>(mouse_handler1);
    
    // Queue the same event again
    event_manager.queue_event<MouseClickEvent>(MouseClickEvent{
        .mouse_x = 100,
        .mouse_y = 200,
        .button = MouseButton::LEFT_MOUSE
    });
    
    // Dispatch events - only handler 2 should be triggered, handler 1 should NOT
    event_manager.dispatch_events();
    EXPECT_FALSE(triggered1);  // Handler 1 should NOT be triggered
    EXPECT_TRUE(triggered2);   // Handler 2 should be triggered
    
    // Reset flags
    triggered2 = false;
    
    // Unsubscribe handler2
    event_manager.unsubscribe<MouseClickEvent>(mouse_handler2);
    
    // Queue the event again
    event_manager.queue_event<MouseClickEvent>(MouseClickEvent{
        .mouse_x = 100,
        .mouse_y = 200,
        .button = MouseButton::LEFT_MOUSE
    });
    
    // Dispatch events - no handler should be triggered
    event_manager.dispatch_events();
    EXPECT_FALSE(triggered1);  // Handler 1 should NOT be triggered
    EXPECT_FALSE(triggered2);  // Handler 2 should NOT be triggered
}

