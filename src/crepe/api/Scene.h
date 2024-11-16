#pragma once

#include <string>

namespace crepe {

class SceneManager;
class ComponentManager;

class Scene {
protected:
	Scene(ComponentManager & mgr, const std::string & name);
	friend class SceneManager;
public:
	virtual ~Scene() = default;

public:
	virtual void load_scene() = 0;
	const std::string name;

protected:
	ComponentManager & component_manager;
};

} // namespace crepe
