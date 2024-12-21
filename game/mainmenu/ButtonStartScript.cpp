#include "ButtonStartScript.h"
#include "api/Rigidbody.h"
#include "api/Transform.h"
#include "iostream"
#include <crepe/api/Camera.h>
#include "MainMenuConfig.h"

using namespace crepe;
using namespace std;

void ButtonStartScript::init(){
	cout << "script init" << endl;
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent& e) { return this->on_button_press(e); });
	this->subscribe<ButtonEnterEvent>([this](const ButtonEnterEvent& e) { return this->on_button_enter(e); });
	this->subscribe<ButtonExitEvent>([this](const ButtonExitEvent& e) { return this->on_button_exit(e); });
}

void ButtonStartScript::frame_update(crepe::duration_t delta_time){
	if(this->transition)
	{
		cout << "transition:" << velocity << std::endl;
		Transform & cam = this->get_components_by_name<Transform>(MainMenuConfig::CAMERA_NAME).front();
		if(velocity < velocity_max && cam.position.x < SLOW_DOWN) velocity += velocity_step * delta_time.count();
		else if(velocity > 20) velocity -= velocity_step * delta_time.count();
		if(cam.position.x < END)	cam.position.x += (velocity * delta_time.count());
		if(cam.position.x >= END) 
		{
			this->set_next_scene(MainMenuConfig::START_SCENE);
		}

	}
}

bool ButtonStartScript::on_button_press(const ButtonPressEvent& e){
	this->transition = true;
	cout << "Start triggered:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool ButtonStartScript::on_button_enter(const ButtonEnterEvent& e){

	cout << "Start Enter:" << e.metadata.game_object_id << std::endl;
	return false;
}
bool ButtonStartScript::on_button_exit(const ButtonExitEvent& e){

	cout << "Start Exit:" << e.metadata.game_object_id << std::endl;
	return false;
}
