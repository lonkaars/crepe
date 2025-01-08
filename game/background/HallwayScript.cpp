#include "HallwayScript.h"

#include "../Config.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void HallwayScript::fixed_update(crepe::duration_t dt) {
	Transform & trans_cam = this->get_components_by_name<Transform>("camera").front();

	float cam_left_x = trans_cam.position.x - VIEWPORT_X / 2;

	if (cam_left_x > this->start_x + this->lenght) {
		//Move whole background 6000 to the right
		RefVector<Transform> trans = this->get_components_by_tag<Transform>("background_hall");
		for (Transform & tran : trans) {
			tran.position.x += 6000;
		}
		this->start_x += 6000;

		//Change sector number
		Animator & anim = this->get_components_by_name<Animator>("hallway_begin").front();
		int column = (current_sector - 1) / 4;
		int row = (current_sector - 1) % 4;
		anim.set_anim(column);
		for (int i = 0; i < row; i++) {
			anim.next_anim();
		}
		RefVector<Sprite> sprites = this->get_components_by_name<Sprite>("hallway_begin");
		switch (current_sector % 7) {
			case 0:
				sprites[1].get().data.color = Color::YELLOW;
				sprites[2].get().data.color = Color::YELLOW;
				break;
			case 1:
				sprites[1].get().data.color = Color::MAGENTA;
				sprites[2].get().data.color = Color::MAGENTA;
				break;
			case 2:
				sprites[1].get().data.color = Color::CYAN;
				sprites[2].get().data.color = Color::CYAN;
				break;
			case 3:
				sprites[1].get().data.color = Color::GREEN;
				sprites[2].get().data.color = Color::GREEN;
				break;
			case 4:
				sprites[1].get().data.color = Color::RED;
				sprites[2].get().data.color = Color::RED;
				break;
			case 5:
				sprites[1].get().data.color = Color::BLUE;
				sprites[2].get().data.color = Color::BLUE;
				break;
			case 6:
				sprites[1].get().data.color = Color::WHITE;
				sprites[2].get().data.color = Color::WHITE;
				break;
		}
		current_sector++;
		if (current_sector > 16) {
			current_sector = 1;
		}
	}
}
