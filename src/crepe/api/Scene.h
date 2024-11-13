#pragma once

#include <string>

namespace crepe {

class ComponentManager;

class Scene {
public:
	Scene(ComponentManager & mgr, const std::string & name);
	virtual ~Scene() = default;

	virtual void load_scene() = 0;

public:
	const std::string name;

protected:
	ComponentManager & component_manager;
};

} // namespace crepe
