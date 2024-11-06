#pragma once

#include <string>

namespace crepe {

class Scene {
public:
	Scene(const std::string & name);
	virtual ~Scene() = default;
	virtual void load_scene() = 0;

public:
	std::string name;
};

} // namespace crepe
