#pragma once

#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Camera.h>
#include <crepe/api/Asset.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Button.h>

using namespace crepe;

class Scene0 : public Scene {
public:
	void load_scene() override;
	std::string get_name() const override;
	//forward call to scene function
	GameObject create_object(const std::string & name, const std::string & tag = "",
						  const vec2 & position = {0, 0}, double rotation = 0,
							double scale = 1);
};
