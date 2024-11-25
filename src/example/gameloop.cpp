#include "crepe/api/LoopManager.h"
#include <crepe/api/EventManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/IKeyListener.h>
#include <crepe/api/IMouseListener.h>
#include <iostream>
using namespace crepe;
class TestKeyListener : public IKeyListener {
public:
	bool on_key_pressed(const KeyPressEvent & event) override {
		std::cout << "TestKeyListener: Key Pressed - Code: " << static_cast<int>(event.key)
				  << std::endl;
		if (event.key == Keycode::ESCAPE) {
		}
		return false;
	}
	bool on_key_released(const KeyReleaseEvent & event) override {
		std::cout << "TestKeyListener: Key Released - Code: " << static_cast<int>(event.key)
				  << std::endl;
		return false;
	}
};
bool on_key_pressed(const KeyPressEvent & event) {
	std::cout << "TestKeyListener: Key Pressed - Code: " << static_cast<int>(event.key)
			  << std::endl;
	if (event.key == Keycode::ESCAPE) {
		return true;
	}
	return false;
}
int main() {
	LoopManager gameloop;
	TestKeyListener key_listener;
	EventManager::get_instance().subscribe<KeyPressEvent>(on_key_pressed);
	gameloop.start();

	return 1;
}
