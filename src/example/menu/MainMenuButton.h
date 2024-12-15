#pragma once

#include <crepe/api/Sprite.h>
// #include "example/menu/MainMenuScript.h"
#include "example/menu/MainMenuScript.h"
#include "example/menu/MenuScene.h"
#include "types.h"
#include <crepe/api/Scene.h>

class MainMenuButton {
public:
	MainMenuButton(MenuScene& from_scene);
private:
	MenuScene& scene;
private:
	void place_btn();
private:
	// Preview
	void place_btn_preview(GameObject & menu,const vec2 &position,const vec2& size,MainMenuScript& script);
	void click_btn_preview();
	// Jetpack
	void place_btn_jetpack(GameObject & menu,const vec2 &position,const vec2& size);
	void click_btn_jetpack();
private:
	void enter_button(Sprite* button_sprite);
	void exit_button(Sprite* button_sprite);
private:
	// Sprite layer
	static constexpr int STARTING_LAYER = 1; 
	// Amount of buttons
	static constexpr int BTN_AMOUNT = 10;    
	// Determines x coordinates
	static constexpr int BTN_OFFSET_COLUM = -950; 
	// Button width for columns
	static constexpr int BTN_WITDH_COLUM = 150;  
	// Starting y coordinate for row
	static constexpr int BTN_START_ROW = 100;    
	// Ending y coordinate for row
	static constexpr int BTN_END_ROW = 1200;     
	// Spacing between buttons in row
	static constexpr int BTN_SPACING_ROW = 8;    
};
