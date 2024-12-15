#include "MainMenuScript.h"
#include "api/Button.h"
#include <iostream>

void MainMenuScript::init() {
  current_tab = MenuTab::NONE;
}

void MainMenuScript::update() {
  switch (current_tab) {
		case MenuTab::JETPACK:
			// Logic for the Jetpack tab
			std::cout << "Jetpack tab is active" << std::endl;
			current_tab = MenuTab::NONE;
			break;
		case MenuTab::PREVIEW:
			// Logic for the Preview tab
			std::cout << "Preview tab is active" << std::endl;
			current_tab = MenuTab::NONE;
			break;
		default:
			//std::cerr << "Unknown tab" << std::endl;
			break;
		}
}

void MainMenuScript::switch_tab(MenuTab tab) {
	current_tab = tab;
}
