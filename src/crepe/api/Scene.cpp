#include "Scene.h"

using namespace crepe;

Scene::Scene(ComponentManager & mgr, const std::string & name)
	: component_manager(mgr),
	  name(name) {}
