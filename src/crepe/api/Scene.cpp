#include "Scene.h"

using namespace crepe;

SaveManager & Scene::get_save_manager() const { return mediator->save_manager; }
