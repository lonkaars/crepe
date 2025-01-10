#pragma once

#include <crepe/api/Script.h>
#include <crepe/manager/SaveManager.h>

class ShopLoadScript : public crepe::Script {
public:
	void init() override;
	bool update();
};
