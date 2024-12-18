
#pragma once

#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>

class Scene1 : public crepe::Scene {
public:
	using crepe::Scene::Scene;
	void load_scene();
	std::string get_name() const { return "Scene1"; };
	crepe::GameObject create_object(const std::string & name, const std::string & tag,
							 const crepe::vec2 & position, double rotation, double scale) {
		return new_object(name, tag, position, rotation, scale);
	}
};
