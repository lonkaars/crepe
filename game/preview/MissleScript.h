#pragma once

#include <crepe/api/Script.h>

class MissleScript : public crepe::Script {
private:
	//crepe::vec2 mouse_pos;
	//bool mouse_click(const crepe::MouseClickEvent & ev);
	bool on_collision(const crepe::CollisionEvent & ev);
	void toggle_render();
public:
	void init();
	void fixed_update(crepe::duration_t dt);
};
