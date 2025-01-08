#pragma once

#include <crepe/api/Script.h>
#include <string>

class IFloatingWindowScript : public virtual crepe::Script {
public:
	virtual void init();
	void disable_all_sprites();
	void enable_all_sprites();

protected:
	std::string tag = "";
};
