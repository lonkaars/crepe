#include "window.h"
#include <iostream>


WindowManager::WindowManager() {
	this->uiRenderer = nullptr;
}


WindowManager::~WindowManager() {
    destroyWindow();
}

bool WindowManager::initWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL.\n";
        return false;
    }

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating SDL Window.\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer.\n";
        return false;
    }

    uiRenderer = new UIRenderer(renderer);
    return true;
}

void WindowManager::destroyWindow() {
    delete uiRenderer;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer* WindowManager::getRenderer() {
    return renderer;
}
void WindowManager::addUIObject(UIObject* uiObject) {
    uiObjects.push_back(uiObject);
}

void WindowManager::renderUIObjects() {
    for (UIObject* obj : uiObjects) {
        uiRenderer->render(obj);
    }
	SDL_RenderPresent(this->renderer);
}
