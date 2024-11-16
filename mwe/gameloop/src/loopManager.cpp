#include "loopManager.h"
#include "timer.h"
LoopManager::LoopManager() { this->window = new WindowManager(); }
LoopManager::~LoopManager() {
	for (GameObject * object : this->objectList) {
		delete object;
	}
	delete this->window;
}
void LoopManager::processInput() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				gameRunning = false;
			} else if (event.key.keysym.sym == SDLK_i) {
				LoopTimer::getInstance().setGameScale(LoopTimer::getInstance().getGameScale()
													  + 0.1);
			} else if (event.key.keysym.sym == SDLK_k) {
				LoopTimer::getInstance().setGameScale(LoopTimer::getInstance().getGameScale()
													  - 0.1);
			}

			break;
	}
}
void LoopManager::fixedUpdate() { fprintf(stderr, "fixed update\n"); }
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

	window->destroyWindow();
}

void LoopManager::setup() {

	LoopTimer::getInstance().start();
	LoopTimer::getInstance().setFPS(10);
	this->gameRunning = true;
	for (int i = 1; i < 3; i++) {
		GameObject * square = new GameObject("square2", i * 60, i * 60, 20, 20, 0, 0);
		objectList.push_back(square);
	}
}
void LoopManager::render() {
	fprintf(stderr, "**********render********** \n");
	if (gameRunning) {
		window->render(objectList);
	}
}

void LoopManager::update() {
	fprintf(stderr, "********** normal update ********** \n");
	LoopTimer & timer = LoopTimer::getInstance();

	float delta = timer.getDeltaTime();
	for (int i = 0; i < objectList.size(); i++) {
		GameObject * obj = objectList[i];

		// Move the object based on its direction
		if (obj->direction == 1) {
			obj->setX(obj->getX() + 50 * delta);
		} else {
			obj->setX(obj->getX() - 50 * delta);
		}

		if (obj->getX() > 500) {
			obj->setX(500);
			obj->direction = 0; // Switch direction to left
		} else if (obj->getX() < 50) {
			obj->setX(50); // Clamp the position to the boundary
			obj->direction = 1; // Switch direction to right
		}
	}
}
