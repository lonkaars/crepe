#include <iostream>
#include <thread>
#include <chrono>
#include "SDLApp.hpp"
#include "ParticleEmitter.hpp"
#include "ParticleSystem.hpp"
#include "Particle.hpp"
#include <chrono>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
    SDLApp app(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!app.initialize()) {
        std::cerr << "Failed to initialize SDLApp." << std::endl;
        return 1;
    }

    ParticleSystem particleSystem;

    unsigned int maxParticles = 100;         // maximum number of particles
    unsigned int emissionRate = 1;          // particles created per second
    unsigned int speed = 50;                 // base speed of particles
    unsigned int speedOffset = 10;           // random offset for particle speed
    unsigned int angle = 90;                 // base angle of particle emission
    unsigned int angleOffset = 30;           // random offset for particle angle
    float beginLifespan = 0.0f;             // beginning lifespan of particles
    float endLifespan = 2.0f;               // ending lifespan of particles

    // Vector to hold all the emitters
    std::vector<ParticleEmitter> emitters;

    // Loop to create 1000 emitters
    for (unsigned int i = 0; i < 1000; ++i) {
        ParticleEmitter emitter(maxParticles, emissionRate, speed, speedOffset, angle, angleOffset, beginLifespan, endLifespan);
        
        // Set a position for each emitter, modifying the position for demonstration
        emitter.m_position = {static_cast<float>(200 + (i % 100)), static_cast<float>(200 + (i / 100) * 10)}; // Adjust position for each emitter
        
        emitters.push_back(emitter); // Add the emitter to the vector
    }
    float deltaTime = 0.1f;
    bool running = true;
    std::cout << "start loop " << std::endl;
    while (running) {
        app.handleEvents(running);

        // Start timing
        auto start = std::chrono::high_resolution_clock::now();

        particleSystem.update(deltaTime, emitters); // update particle system with delta time and emitters

        // End timing
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float, std::milli> duration = end - start; // get duration in milliseconds

        std::cout << "Update took " << duration.count() << " ms" << std::endl;
        app.clearScreen();

        start = std::chrono::high_resolution_clock::now();
        // render particles using the drawSquare method from SDLApp
        for (const ParticleEmitter& emitter : emitters) {
            for (const Particle& particle : emitter.particles) {
                if(particle.active)app.drawSquare(particle.position.x, particle.position.y, 5); // draw each particle
            }
        }
        

        app.presentScreen();
        end = std::chrono::high_resolution_clock::now();
         duration = end - start; // get duration in milliseconds

        std::cout << "screen took " << duration.count() << " ms" << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // simulate ~50 FPS
    }

    app.cleanUp();
    return 0;
}
