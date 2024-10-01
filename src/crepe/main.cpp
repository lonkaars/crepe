#include <iostream>
#include <thread>
#include <chrono>
#include <SDL.h>
#include "ParticleEmitter.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void renderParticles(SDL_Renderer* renderer, const ParticleEmitter& emitter) {
    for (const auto& particle : emitter.particles) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
        SDL_Rect rect = { particle.position.x, particle.position.y, 5, 5 }; 
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int argc, char* argv[]) {
  
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Initialization Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Particle System",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    ParticleEmitter emitter(100, 10.0f);
    emitter.position = { 400, 300 };
    ParticleEmitter emitter2(100, 10.0f);
    emitter2.position = { 600, 600 }; 

    float deltaTime = 0.1f;

    bool running = true;
    SDL_Event event;
    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        emitter.update(deltaTime);
        emitter2.update(deltaTime);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);

        renderParticles(renderer, emitter);
        renderParticles(renderer, emitter2);

        SDL_RenderPresent(renderer);

        
    }

  
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
