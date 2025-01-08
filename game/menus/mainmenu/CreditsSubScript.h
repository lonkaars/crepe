#pragma once

#include "../IButtonScript.h"
#include "../IFloatingWindowScript.h"

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>

struct ShowCreditsEvent : public crepe::Event {};

class CreditsSubScript : public IFloatingWindowScript, public IButtonScript {
public:
	CreditsSubScript(const std::string & tag);
	void init() override;
	bool disable_all();
	bool enable_all();
	bool on_button_press(const crepe::ButtonPressEvent & e);
};
