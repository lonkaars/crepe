

#include "../crepe/api/GameObject.h"
#include "api/BehaviorScript.h"
#include "api/Transform.h"
#include "api/eventManager.h"

#include <crepe/api/Animator.h>
#include <crepe/api/event.h>
#include <crepe/api/Script.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/loopManager.h>

using namespace crepe;
using namespace std;

enum PlayerAnimation {
	WALK_DOWN = 0,
	WALK_LEFT = 1,
	WALK_RIGHT = 2,
	WALK_UP = 3,
};

struct PlayerMovement {
	bool moving_left = false;
	bool moving_right = false;
	bool moving_up = false;
	bool moving_down = false;

	double x = 0;
	double y = 0;
	double rot = 0;
	double scale = 0;
};

PlayerMovement player;
const int SPEED = 5;
void on_key_pressed(const KeyPressedEvent & e) {
    // Set movement flags based on key press
    switch (e.getKeyCode()) {
        case A:  
            player.moving_left = true;
            break;
        case D:  
            player.moving_right = true;
            break;
        case W:  
            player.moving_up = true;
            break;
        case S:  
            player.moving_down = true;
            break;
        default:
            break;
    }
}

class PlayerScript : public Script {
    void update() override {
        auto animators = this->get_components<Animator>();
        auto & transform = this->get_component<Transform>();

        // Reset animator states before setting active one
        for (auto& animator : animators) {
            animator.get().active = false;
        }

        // Update player position based on movement direction
        if (player.moving_left) {
            player.x -= SPEED;
            animators[WALK_LEFT].get().active = true;
        } else if (player.moving_right) {
            player.x += SPEED;
            animators[WALK_RIGHT].get().active = true;
        } else if (player.moving_up) {
            player.y -= SPEED;
            animators[WALK_UP].get().active = true;
        } else if (player.moving_down) {
            player.y += SPEED;
            animators[WALK_DOWN].get().active = true;
        }

        transform.position.x = player.x;
        transform.position.y = player.y;

        player.moving_left = player.moving_right = player.moving_up = player.moving_down = false;
    }
};

int main() {
	LoopManager mgr;

	GameObject animatie_test(0, "body", "person", Point{0, 0}, 0, 1);
	subscribe<KeyPressedEvent>(on_key_pressed);

	{
		Color color(0, 0, 0, 0);
		Sprite & test = animatie_test.add_component<Sprite>(
			std::make_shared<Texture>(
				"../asset/spritesheet/pokemon_ss.png"),
			color, FlipSettings{false, false});
		animatie_test.add_component<Animator>(test, 4, 4, PlayerAnimation::WALK_DOWN);
		animatie_test.add_component<Animator>(test, 4, 4, PlayerAnimation::WALK_LEFT);
		animatie_test.add_component<Animator>(test, 4, 4, PlayerAnimation::WALK_RIGHT);
		animatie_test.add_component<Animator>(test, 4, 4, PlayerAnimation::WALK_UP);
		animatie_test.add_component<BehaviorScript>().set_script<PlayerScript>();
		animatie_test.add_component<Camera>(Color::get_white());
	}

	mgr.setRunning(true);
	mgr.setup();
	mgr.loop();
	return 0;
}
