#include "ViewFacade.hpp"
#include <iostream>

ViewFacade::ViewFacade() : window(nullptr), renderer(nullptr), running(false) {}

ViewFacade::~ViewFacade() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool ViewFacade::initialize(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    running = true;
    return true;
}

void ViewFacade::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderClear(renderer);
}

void ViewFacade::present() {
    SDL_RenderPresent(renderer);
}

void ViewFacade::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

bool ViewFacade::isRunning() const {
    return running;
}

void ViewFacade::drawSquare(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Rect square;
    square.x = x;
    square.y = y;
    square.w = w;
    square.h = h;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &square);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black outline
    SDL_RenderDrawRect(renderer, &square);
}

void ViewFacade::updateDeltaTime() {
    Uint32 currentTime = SDL_GetTicks();
    deltaTime = (currentTime - lastFrameTime) / 1000.0f; // Convert to seconds
    lastFrameTime = currentTime;
}

float ViewFacade::getDeltaTime() const {
    return deltaTime;
}

bool ViewFacade::isSpacePressed() const {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    return currentKeyStates[SDL_SCANCODE_SPACE];
}
