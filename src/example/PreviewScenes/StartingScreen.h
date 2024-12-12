
#pragma once


#include <crepe/api/Scene.h>


class StartScene : public crepe::Scene {
public:
	using crepe::Scene::Scene;
	void load_scene();
	std::string get_name() const { return "Start Scene"; };
};
