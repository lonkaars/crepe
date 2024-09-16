#include "loopManager.h"
LoopManager::LoopManager(){
}
void LoopManager::processInput(){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE){
				gameRunning = false;
			}
		break;
	}
}
void LoopManager::loop(){
	while(gameRunning){
		//processInput();
		//update();
		//render();
	}
	window.destroyWindow();
}
void LoopManager::setup(){
	gameRunning = window.initWindow();
}
void LoopManager::render(){
	if(gameRunning){
		SDL_SetRenderDrawColor(window.getRenderer(),255,0,0,255);
		SDL_RenderClear(window.getRenderer());
	}
}
void LoopManager::update(){

}
