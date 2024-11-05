#pragma once

#include <string>

namespace crepe::api {

class Scene {
public:
	Scene(std::string name);
	virtual ~Scene() = default;
	virtual void load_scene() = 0;

public:
	std::string name;
};

} // namespace crepe::api
