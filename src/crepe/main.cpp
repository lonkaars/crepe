#include <iostream>
#include <thread>
#include <chrono>
#include "SDLApp.hpp"
#include "ParticleEmitter.hpp"
#include "ParticleSystem.hpp"
#include "Particle.hpp"

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
    unsigned int emissionRate = 10;          // particles created per second
    unsigned int speed = 50;                 // base speed of particles
    unsigned int speedOffset = 10;           // random offset for particle speed
    unsigned int angle = 90;                 // base angle of particle emission
    unsigned int angleOffset = 30;           // random offset for particle angle

    ParticleEmitter emitter1(maxParticles, emissionRate, speed, speedOffset, angle, angleOffset);
    emitter1.m_position = {200, 200};  // set the position of the first emitter

    ParticleEmitter emitter2(maxParticles, emissionRate, speed, speedOffset, angle - 90, angleOffset); // Another emitter
    emitter2.m_position = {200, 150};  // set the position of the second emitter

    std::vector<ParticleEmitter> emitters = {  emitter2 }; // array of emitters

    float deltaTime = 0.1f;
    bool running = true;

    while (running) {
        app.handleEvents(running);

        particleSystem.update(deltaTime, emitters); // update particle system with delta time and emitters

        app.clearScreen();

        // render particles using the drawSquare method from SDLApp
        for (const ParticleEmitter& emitter : emitters) {
            for (const Particle& particle : emitter.particles) {

                app.drawSquare(particle.position.x, particle.position.y, 5); // draw each particle
            }
        }

        app.presentScreen();

        std::this_thread::sleep_for(std::chrono::milliseconds(20)); // simulate ~50 FPS
    }

    app.cleanUp();
    return 0;
}
