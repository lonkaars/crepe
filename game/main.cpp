#include <crepe/api/Engine.h>
#include <crepe/api/Script.h>

#include "GameScene.h"
#include "PreviewScene.h"

using namespace crepe;

int main() {
	Engine gameloop;
	gameloop.add_scene<PreviewScene>();

	return gameloop.main();
}
