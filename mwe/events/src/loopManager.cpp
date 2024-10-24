#include "loopManager.h"

LoopManager::LoopManager() {}
void LoopManager::processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_KEYDOWN:
			triggerEvent(KeyPressedEvent(getCustomKey(event.key.keysym.sym)));
			break;
		case SDL_MOUSEBUTTONDOWN:
            int x, y;
            SDL_GetMouseState(&x, &y); 
            triggerEvent(MousePressedEvent(x, y)); 
            break;
	}
}
void LoopManager::setRunning(bool running){
	this->gameRunning = running;
}
void LoopManager::fixedUpdate() { 
	//fprintf(stderr, "fixed update\n"); 
}
void LoopManager::loop() {
	LoopTimer & timer = LoopTimer::getInstance();
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
void onKey(const KeyPressedEvent& e)
{
   	int keyCode = e.getKeyCode();
	std::cout << "keycode pressed: " << keyCode << std::endl;

}
void onMouse(const MousePressedEvent& e){
		fprintf(stderr, "mouse Position X: %d Y: %d\n", e.getMousePosition().first, e.getMousePosition().second);
}
void LoopManager::setup() {
	gameRunning = window.initWindow();
	LoopTimer::getInstance().start();
	LoopTimer::getInstance().setFPS(50);
	EventHandler<KeyPressedEvent> callback = onKey;
    subscribe<KeyPressedEvent>(callback,false);
	EventHandler<MousePressedEvent> mouseCallback = onMouse;
    subscribe<MousePressedEvent>(mouseCallback ,false);
	EventHandler<KeyPressedEvent> closeWindowCallback = [this](const KeyPressedEvent& e) {
		if(e.getKeyCode() == Escape){
			this->setRunning(false);
		}
    };
    subscribe<KeyPressedEvent>(closeWindowCallback,false);

}
void LoopManager::render() {
	//fprintf(stderr, "**********render********** \n");
	if (gameRunning) {
		//window.render(objectList);
	}
}

void LoopManager::update() {
	//fprintf(stderr, "**********normal update********** \n");
	LoopTimer & timer = LoopTimer::getInstance();

	float delta = timer.getDeltaTime();

	// for (int i = 0; i < objectList.size(); i++) {
	// 	objectList[i]->setX(objectList[i]->getX() + 50 * delta);
	// 	objectList[i]->setY(objectList[i]->getY() + 50 * delta);
	// }
}
