#pragma once

#include <string>

#include <crepe/api/Scene.h>

class ShopMenuScene : public crepe::Scene {
public:
	void load_scene();

	std::string get_name() const;
};
