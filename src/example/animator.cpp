

#include "../crepe/api/GameObject.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/loopManager.h>

using namespace crepe;
using namespace std;

int main() {
	LoopManager mgr;

	GameObject animatie_test(0, "body", "person", Point{0, 0}, 0, 1);

	{
		Color color(0, 0, 0, 0);
		Sprite & test = animatie_test.add_component<Sprite>(
			std::make_shared<Texture>(
				"../asset/spritesheet/spritesheet_test.png"),
			color, FlipSettings{false, false});
		test.active = false;
		animatie_test.add_component<Animator>(test, 4, 1, 0);
		animatie_test.add_component<Camera>(Color::get_white());
	}

	mgr.setRunning(true);
	mgr.setup();
	mgr.loop();
	return 0;
}
