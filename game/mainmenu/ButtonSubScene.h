#pragma once

#include <crepe/api/GameObject.h>

namespace crepe {
class Scene;
}

class ButtonSubScene {
public:
	void create(crepe::Scene & scn);
private:
	void large_btn_overlay(crepe::GameObject & button_object);
};
