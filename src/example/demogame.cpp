#include <crepe/api/LoopManager.h>
#include <crepe/api/Scene.h>
#include "playerScript.h"
#include "scene1.h"
using namespace crepe;
int main(){
	LoopManager loop_mgr;
	
	loop_mgr.add_scene<Scene1>();
	loop_mgr.start();
	return 0;	
}
