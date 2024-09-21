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
void LoopManager::fixedUpdate(){
	fprintf(stderr,"fixed update\n");
}
void LoopManager::loop() {
    LoopTimer& timer = LoopTimer::getInstance();
    timer.start();

    while (gameRunning) {
        timer.update();

        while (timer.getLag() >= timer.getFixedDeltaTime()) {
            processInput();
            fixedUpdate();
            timer.advanceFixedUpdate();
        }

        update();
        render();

        timer.enforceFrameRate();
    }

    window.destroyWindow();
}

void LoopManager::setup(){
	gameRunning = window.initWindow();
	LoopTimer::getInstance().start();
	LoopTimer::getInstance().setFPS(50);
	
	for(int i = 0; i < 2;i++){
		GameObject* square = new GameObject("square2",i*40,i*40,20,20,0,0);
		objectList.push_back(square);
	}
}
void LoopManager::render(){
	fprintf(stderr,"**********render********** \n");
	if(gameRunning){
		window.render(objectList);
	}
}

void LoopManager::update() {
	fprintf(stderr,"**********normal update********** \n");
    LoopTimer& timer = LoopTimer::getInstance();
	
    float delta= timer.getDeltaTime();

    for (int i = 0; i < objectList.size(); i++) {
        objectList[i]->setX(objectList[i]->getX() + 50 * delta); 
        objectList[i]->setY(objectList[i]->getY() + 50 * delta);
    }
}

