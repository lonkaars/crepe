#pragma once

#include <crepe/api/Script.h>

class MissleScript : public crepe::Script {
private:
	crepe::vec2 mouse_pos;
	bool mouse_click(const crepe::MouseClickEvent & ev);
public:
	void init();
	void fixed_update(crepe::duration_t dt);
};
