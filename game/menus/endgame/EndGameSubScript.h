#pragma once

#include "../IFloatingWindowScript.h"

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

struct ShowScoreEvent : public crepe::Event {};

class EndGameSubScript : public IFloatingWindowScript {
public:
	EndGameSubScript(const std::string & tag);
	void init() override;
	bool disable_all();
	bool enable_all();
	bool reset_timescale();
	bool showscore();
};
