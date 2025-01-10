#pragma once

#include <crepe/api/Script.h>

class AlertScript : public crepe::Script {
private:
	bool has_alert = false;

public:
	void fixed_update(crepe::duration_t dt);
};
