#include "loopManager.h"
#include "timer.h"
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
	fprintf(stderr,"loop. \n");
	while(gameRunning){
		//Timer::getInstance().update();
        //deltaTime = Timer::getInstance().getDeltaTime();
		processInput();
		update();
		render();
	}
	window.destroyWindow();
}
void LoopManager::setup(){
	gameRunning = window.initWindow();
	LoopTimer::getInstance().start();
	LoopTimer::getInstance().setFPS(210);
	
	for(int i = 0; i < 2;i++){
		GameObject* square2 = new GameObject("square2",i*40,i*40,20,20,0,0);
		objectList.push_back(square2);
	}
}
void LoopManager::render(){
	if(gameRunning){
		window.render(objectList);
	}
}

void LoopManager::update() {
    LoopTimer& timer = LoopTimer::getInstance();
    timer.enforceFrameRate();
    timer.update();
    float delta= timer.getDeltaTime();

    for (int i = 0; i < objectList.size(); i++) {
        objectList[i]->setX(objectList[i]->getX() + 50 * delta); 
        objectList[i]->setY(objectList[i]->getY() + 50 * delta);
    }
}

