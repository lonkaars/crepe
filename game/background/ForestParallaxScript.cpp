#include "ForestParallaxScript.h"

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
}
