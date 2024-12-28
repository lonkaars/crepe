#pragma once

#include <crepe/api/Script.h>

class ITransitionScript : public virtual crepe::Script {
public:
	void frame_update(crepe::duration_t delta_time) override;
	virtual const char* get_scene_name() const = 0;
private:
	float velocity = 20;
protected:
	bool transition = false;
};
