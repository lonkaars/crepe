#include "ITransitionScript.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "iostream"
#include <crepe/api/Camera.h>
#include "MainMenuConfig.h"
#include "types.h"

using namespace crepe;
using namespace std;

void ITransitionScript::frame_update(crepe::duration_t delta_time){
	if(this->transition)
	{
		// cout << "transition:" << velocity << std::endl;
		Transform & cam = this->get_components_by_name<Transform>(MainMenuConfig::CAMERA_NAME).front();
		RefVector<Transform> info_tf = this->get_components_by_tag<Transform>(MainMenuConfig::MENU_INFO_TAG);
		for (Transform & tf : info_tf) {
			tf.position.y -= MainMenuConfig::VELOCITY_INFO_UP * delta_time.count();
		}
		if(velocity < MainMenuConfig::VELOCITY_MAX && cam.position.x < MainMenuConfig::SLOW_DOWN) velocity += MainMenuConfig::VELOCITY_STEP * delta_time.count();
		else if(velocity > 20) velocity -= MainMenuConfig::VELOCITY_STEP * delta_time.count();
		if(cam.position.x < MainMenuConfig::END)	cam.position.x += (velocity * delta_time.count());
		if(cam.position.x >= MainMenuConfig::END) 
		{
			this->set_next_scene(this->get_scene_name());
		}

	}
}

