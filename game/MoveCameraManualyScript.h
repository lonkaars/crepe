#pragma once

#include <crepe/api/Script.h>

class MoveCameraManualyScript : public crepe::Script {
public:
	void init();

private:
	bool keypressed(const crepe::KeyPressEvent & event);
};
