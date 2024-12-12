












#include "example/PreviewScenes/StartingScreen.h"
#include <crepe/api/LoopManager.h>


using namespace crepe;


int main(){
	LoopManager engine;

	engine.add_scene<StartScene>();

	engine.start();

};
