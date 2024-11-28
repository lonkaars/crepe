#pragma once

#include <crepe/api/Transform.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Script.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/Event.h>
#include <crepe/api/KeyCodes.h>
using namespace crepe;
using namespace std;
class PlayerScript : public Script {
		// NOTE: default (private) visibility of init and update shouldn't cause
		// issues!
		bool on_key_press(const KeyPressEvent& e){
			Transform& transform = get_component<Transform>();
			switch(e.key){
				// case Keycode::A:
				// transform.position.x -= 5;
				// break;
				// case Keycode::D:
				// transform.position.x += 5;
				// break;
				// case Keycode::W:
				// transform.position.y += 5;
				// break;
				// case Keycode::S:
				// transform.position.y -= 5;
				// break;
				case Keycode::SPACE:
					transform.position.y += 10;
					break;
				case Keycode::ENTER:
					//spawn bullet or something
					break;
			}
			return false;
		}
		void init() {
			//this->position = OptionalRef(get_component<Transform>());
			subscribe<KeyPressEvent>([this](const KeyPressEvent & e) {
				return on_key_press(e);
			});
		}
		void update() {}

	public:
		//OptionalRef<Transform> position;
	};
