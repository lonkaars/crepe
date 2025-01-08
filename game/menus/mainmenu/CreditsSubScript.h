#pragma once

#include "../IFloatingWindowScript.h"

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

class CreditsSubScript : public IFloatingWindowScript {
public:
	CreditsSubScript(const std::string & tag);
	void init() override;
	bool disable_all();
	bool enable_all();
};
