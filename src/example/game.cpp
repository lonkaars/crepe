#include "GameScene.h"

#include <crepe/api/LoopManager.h>

using namespace crepe;
using namespace std;

int main(int argc, char * argv[]) {
	LoopManager gameloop;
	gameloop.add_scene<GameScene>();
	gameloop.start();
	return 0;
}
