#pragma once

#include "../IFloatingWindowScript.h"
#include "api/Event.h"
#include <crepe/api/Script.h>

class EndGameSubScript : public IFloatingWindowScript {
public:
	EndGameSubScript(const std::string & tag);
 	void init() override;
	bool disable_all();
	bool enable_all();
	bool reset_timescale();
};


