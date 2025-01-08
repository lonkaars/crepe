#pragma once

#include <crepe/api/Scene.h>
#include <string>

class PreviewScene : public crepe::Scene {
public:
	void load_scene();

	std::string get_name() const;
};
