#include <crepe/api/Engine.h>
#include <crepe/api/Script.h>

#include "GameScene.h"
#include "menus/mainmenu/MainMenuScene.h"
#include "menus/shop/ShopMenuScene.h"


using namespace crepe;

int main() {
	Engine gameloop;
	gameloop.add_scene<MainMenuScene>();
	gameloop.add_scene<ShopMenuScene>();
	gameloop.add_scene<GameScene>();

	return gameloop.main();
}
