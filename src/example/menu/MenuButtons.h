#pragma once

#include <crepe/api/Scene.h>

class MainMenuButton {
public:
	MainMenuButton(crepe::Scene& from_scene);
private:
	crepe::Scene& scene;
private:
	void calculate_btn_pos();
	void place_btn();
	void place_btn_preview();
};
