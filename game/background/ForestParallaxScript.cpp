#include "ForestParallaxScript.h"

#include "../Config.h"

using namespace crepe;
using namespace std;

ForestParallaxScript::ForestParallaxScript(
	float begin_x, float end_x, std::string unique_bg_name
)
	: begin_x(begin_x),
	  end_x(end_x),
	  name(unique_bg_name) {}

void ForestParallaxScript::fixed_update(crepe::duration_t dt) {
	RefVector<Transform> vec_2
		= this->get_components_by_name<Transform>("forest_bg_2_" + name);
	RefVector<Transform> vec_3
		= this->get_components_by_name<Transform>("forest_bg_3_" + name);

	for (Transform & t : vec_2) {
		if (t.position.x > end_x - 400) {
			t.position.x = begin_x - 400;
		}
	}
	for (Transform & t : vec_3) {
		if (t.position.x > end_x - 400) {
			t.position.x = begin_x - 400;
		}
	}

	//Move whole background 12000 to the right
	Transform & trans_cam = this->get_components_by_name<Transform>("camera").front();

	float cam_left_x = trans_cam.position.x - VIEWPORT_X / 2;

	if (cam_left_x > this->start_x + this->lenght) {
		//Move whole background 12000 to the right
		RefVector<Transform> trans
			= this->get_components_by_tag<Transform>("background_forest");
		for (Transform & tran : trans) {
			tran.position.x += 12000;
		}
		this->start_x += 12000;

		RefVector<Transform> trans_back
			= this->get_components_by_tag<Transform>("forest_background");
		for (Transform & tran : trans_back) {
			tran.position.x += 12000;
		}

		begin_x += 12000;
		end_x += 12000;
	}
}
