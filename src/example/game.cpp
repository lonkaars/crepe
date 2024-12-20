#include "GameScene.h"

#include <crepe/api/Engine.h>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	Engine gameloop;
	gameloop.add_scene<GameScene>();

	return gameloop.main();
}
