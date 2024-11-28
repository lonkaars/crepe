#pragma once

#include <iostream>
#include <chrono>
#include <crepe/api/Transform.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Script.h>
#include <crepe/api/EventManager.h>
#include <crepe/api/Event.h>
#include <crepe/api/KeyCodes.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/GameObject.h>
using namespace crepe;
using namespace std;

class PlayerScript : public Script {
    using Clock = std::chrono::steady_clock;
    bool on_key_press(const KeyPressEvent& e) {
        auto now = Clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - last_key_time).count() < min_key_interval_ms) {
            return false;
        }
        last_key_time = now;

        Transform& transform = get_component<Transform>();
        Rigidbody& rigid_body = get_component<Rigidbody>();
		float movementspeed = 5;
        switch (e.key) {
			case Keycode::Q:
				rigid_body.data.angular_velocity -= 0.3;
			break;
			case Keycode::E:
				rigid_body.data.angular_velocity += 0.3;
			break;
			case Keycode::A:
				rigid_body.add_force_linear(vec2{-movementspeed,0});
			break;
			case Keycode::D:
				rigid_body.add_force_linear(vec2{movementspeed,0});
			break;
			case Keycode::W:
				rigid_body.add_force_linear(vec2{0,-movementspeed});
			break;
			case Keycode::S:
				rigid_body.add_force_linear(vec2{0,movementspeed});
			break;
            case Keycode::SPACE:
                std::cout << "space pressed\n";
                rigid_body.add_force_linear(vec2{0, movementspeed});
                break;
            case Keycode::ENTER:
                std::cout << "enter pressed\n";
                this->spawn_bullet();
                break;
            case Keycode::ESCAPE:
                std::cout << "escape pressed\n";
                EventManager::get_instance().trigger_event<ShutDownEvent>(ShutDownEvent{});
                break;
        }
        return false;
    }
	void spawn_bullet(){
		// ComponentManager& mgr = component_manager;
		// // component manager nodig om nieuwe bullet te maken
		// GameObject bullet = mgr.new_object("bullet", "tag_scene1",vec2{-999,-999}, 90,1);
		// auto& bullet_sprite = bullet.add_component<Sprite>(make_shared<Texture>("asset/texture/bullet.png"),Color(0, 0, 0, 0),FlipSettings{false, false});
	}
    void init() {
        subscribe<KeyPressEvent>([this](const KeyPressEvent & e) {
            return on_key_press(e);
        });
    }

    void update() {}

public:
    PlayerScript() : last_key_time(Clock::now()), min_key_interval_ms(200) {}

private:
    Clock::time_point last_key_time;   // Time point of the last handled key press
    int min_key_interval_ms;          // Minimum interval between key presses in milliseconds
};
