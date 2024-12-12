
#pragma once

#include <crepe/api/Scene.h>

class Scene1 : public crepe::Scene {
public:
	using crepe::Scene::Scene;
	void load_scene();
	std::string get_name() const { return "Scene1"; };
};
