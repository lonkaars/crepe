#include "ITransitionScript.h"
#include "MainMenuConfig.h"

#include "../MenusConfig.h"
#include "../../Config.h"

#include <crepe/api/Camera.h>
#include <crepe/api/Transform.h>
#include <crepe/types.h>

using namespace crepe;
using namespace std;

void ITransitionScript::frame_update(crepe::duration_t delta_time) {
	if (this->transition) {
		// cout << "transition:" << velocity << std::endl;
		Transform & cam = this->get_components_by_name<Transform>(CAMERA_NAME).front();
		RefVector<Transform> info_tf = this->get_components_by_tag<Transform>(MENU_INFO_TAG);
		for (Transform & tf : info_tf) {
			tf.position.y -= VELOCITY_INFO_UP * delta_time.count();
		}
		if (velocity < VELOCITY_MAX && cam.position.x < SLOW_DOWN)
			velocity += VELOCITY_STEP * delta_time.count();
		else if (velocity > 20) velocity -= VELOCITY_STEP * delta_time.count();
		if (cam.position.x < END) cam.position.x += (velocity * delta_time.count());
		if (cam.position.x >= END) {
			this->set_next_scene(this->get_scene_name());
		}
	}
}
