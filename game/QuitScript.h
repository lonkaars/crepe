#pragma once

#include <crepe/api/Script.h>

class QuitScript : public crepe::Script {
private:
	bool on_event(const crepe::KeyPressEvent & ev);

public:
	void init();
};
