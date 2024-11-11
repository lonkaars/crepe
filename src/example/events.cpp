#include <iostream>

#include <crepe/ComponentManager.h>
#include <crepe/system/ScriptSystem.h>
#include <crepe/util/log.h>

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Config.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Transform.h>

#include "crepe/api/Event.h"
#include "crepe/api/EventManager.h"
#include "crepe/api/IKeyListener.h"
#include "crepe/api/IMouseListener.h"
using namespace crepe;
using namespace std;
class MyScript : public Script, public IKeyListener,public IMouseListener{
	void update() {
		// Retrieve component from the same GameObject this script is on
		Transform & test = get_component<Transform>();
		dbg_logf("Transform(%.2f, %.2f)", test.position.x, test.position.y);
	}

	bool on_key_pressed(const KeyPressEvent & event) override{
		std::cout << "KeyPressed function" << std::endl;
		return false;
	}
	bool on_key_released(const KeyReleaseEvent & event) override{
		std::cout << "KeyRelease function" << std::endl;
		return false;
	}
	bool on_mouse_clicked(const MouseClickEvent & event){
		std::cout << "MouseClick function" << std::endl;
		return false;
	}
    bool on_mouse_pressed(const MousePressEvent & event){
		std::cout << "MousePress function" << std::endl;
		return false;
	}
    bool on_mouse_released(const MouseReleaseEvent & event){
		std::cout << "MouseRelease function" << std::endl;
		return false;
	}
    bool on_mouse_moved(const MouseMoveEvent & event){
		std::cout << "MouseMove function" << std::endl;
		return false;
	}

};
class TestKeyListener : public IKeyListener {
public:
    bool on_key_pressed(const KeyPressEvent &event) override {
        std::cout << "TestKeyListener: Key Pressed - Code: " << event.key << std::endl;
        return true;  // Return true if the listener should remain active
    }
    bool on_key_released(const KeyReleaseEvent &event) override {
        std::cout << "TestKeyListener: Key Released - Code: " << event.key << std::endl;
        return true;
    }
};
int main() {
    {
        // Instantiate TestKeyListener, which subscribes to key events
        TestKeyListener testListener;

        // Create game object with Transform and BehaviorScript components
        auto obj = GameObject(0, "name", "tag", Vector2{1.2, 3.4}, 0, 1);
        obj.add_component<BehaviorScript>().set_script<MyScript>();

        // Get ScriptSystem singleton instance (this would normally be done from the game loop)
        ScriptSystem sys;
        sys.update();

        // Trigger some events
        KeyPressEvent key_press;
        key_press.key = 1;
        key_press.repeat = 0;

        MouseClickEvent click_event;
        click_event.button = MouseButton::LEFT_MOUSE;
        click_event.mouse_x = 100;
        click_event.mouse_y = 200;
		std::cout << "testing custom listener:" << std::endl;
        // Trigger the events while `testListener` is in scope
        EventManager::get_instance().trigger_event<KeyPressEvent>(key_press, 0);
        EventManager::get_instance().trigger_event<MouseClickEvent>(click_event, 0);
    } // End of scope - triggers destruction of obj, MyScript, and `testListener`, unsubscribing from events
    // After `testListener` is destroyed, triggering events again should have no output if unsubscription worked
    KeyPressEvent key_press;
    key_press.key = 1;
    key_press.repeat = 0;
    EventManager::get_instance().trigger_event<KeyPressEvent>(key_press, 0);

    MouseClickEvent click_event;
    click_event.button = MouseButton::LEFT_MOUSE;
    click_event.mouse_x = 100;
    click_event.mouse_y = 200;
    EventManager::get_instance().trigger_event<MouseClickEvent>(click_event, 0);

    return EXIT_SUCCESS;
}


