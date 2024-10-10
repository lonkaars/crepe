#include "SDLApp.h"
#include <iostream>
#include <vector>
#include "Particle.h"
#include "ParticleEmitter.h"

SDLApp::SDLApp(int windowWidth, int windowHeight)
    : windowWidth(windowWidth), windowHeight(windowHeight), window(nullptr), renderer(nullptr) {}

SDLApp::~SDLApp() {
    cleanUp();
}

bool SDLApp::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Particle System",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowWidth,
                              windowHeight,
                              SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void SDLApp::handleEvents(bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void SDLApp::clearScreen() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
    SDL_RenderClear(renderer);
}

void SDLApp::presentScreen() {
    SDL_RenderPresent(renderer);
}

void SDLApp::drawSquare(int x, int y, int size) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
    SDL_Rect rect = { x, y, size, size };
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Texture* squareTexture = nullptr; // Load this with an image or create it





void SDLApp::cleanUp() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
