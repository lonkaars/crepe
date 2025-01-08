#pragma once

#include <crepe/api/Script.h>

class IButtonScript : public virtual crepe::Script {
public:
	virtual void init();
	virtual bool on_button_exit(const crepe::ButtonExitEvent & e);
	virtual bool on_button_enter(const crepe::ButtonEnterEvent & e);
};
