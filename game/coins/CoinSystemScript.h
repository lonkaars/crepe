#pragma once

#include "CoinSystem.h"
#include "api/Script.h"

class CoinSystemScript : public crepe::Script {
public:
	CoinSystemScript() {};
	// void init() override;
	void frame_update(crepe::duration_t dt) override;
private:
	CoinSystem coin_system;
};
