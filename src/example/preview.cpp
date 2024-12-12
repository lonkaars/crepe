












#include "example/PreviewScenes/Scene1.h"
#include "example/PreviewScenes/StartingScreen.h"
#include <crepe/api/LoopManager.h>


using namespace crepe;


int main(){
	LoopManager engine;

	engine.add_scene<StartScene>();
	engine.add_scene<Scene1>();

	engine.start();

};
