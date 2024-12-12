

#include "StartingScreen.h"



#include <crepe/api/Asset.h>
#include <crepe/api/Script.h>
#include <crepe/api/Event.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Color.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/manager/ComponentManager.h>
#include <crepe/manager/Mediator.h>
#include <crepe/types.h>
#include <crepe/api/KeyCodes.h>

using namespace crepe;

class NextScene : public Script {
	bool key_pressed(const KeyPressEvent & ev){
		switch (ev.key) {
			case Keycode::ENTER:
				this->set_next_scene("Scene1");
				break;
			default:
				break;
		}
		return false;
	}

	void init() {
		subscribe<KeyPressEvent>([this](const KeyPressEvent & ev) -> bool {
			return this->key_pressed(ev);
	});
	}

	void update() {}
};

void StartScene::load_scene() {
	Mediator & mediator = this->mediator;
	ComponentManager & mgr = mediator.component_manager;

	GameObject cam = mgr.new_object("CAMERA");
	cam.add_component<Camera>(ivec2{1080, 720}, vec2{812, 543},
							  Camera::Data{
								  .bg_color = Color::WHITE,
							  });

	Asset bg_lowest{"assets/bg.png"};
	Asset bg{"assets/Levels/Title/Objects/title_small.png"};

	cam.add_component<Sprite>(bg_lowest, Sprite::Data{
											 .color = Color(255, 255, 255, 10),
											 .size{812, 0},
										 });
	cam.add_component<Sprite>(bg, Sprite::Data{
									  .size{812, 0},
								  });
	cam.add_component<BehaviorScript>().set_script<NextScene>();
}
