#pragma once

#include "Component.h"

#include "api/EventHandler.h"
namespace crepe {

class UiObject : public Component{
public:
	UiObject(game_object_id_t id) : Component(id){};
	int width = 0;
	int height = 0;
public:
virtual int get_instances_max() const { return 1; }
};

}
