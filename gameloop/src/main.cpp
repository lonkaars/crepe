//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
//#include "window.h"
#include "loopManager.h"
//Screen dimension constants


//Starts up SDL and creates window

int main( int argc, char* args[] )
{
	LoopManager gameLoop;
	gameLoop.setup();
	gameLoop.loop();
	return 0;
}
