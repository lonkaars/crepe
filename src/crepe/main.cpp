#include <iostream>
#include <thread>
#include <chrono>
#include "SDLApp.hpp"
#include "ParticleEmitter.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
    SDLApp app(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!app.initialize()) {
        std::cerr << "Failed to initialize SDLApp." << std::endl;
        return 1;
    }


    unsigned int maxParticles = 100;         //maximum number of particles
    unsigned int emissionRate = 10;     //particles created per second
    unsigned int speed = 50;            //base speed of particles
    unsigned int speedOffset = 10;      //random offset for particle speed
    unsigned int angle = 180;             //base angle of particle emission
    unsigned int angleOffset = 30;      //random offset for particle angle


    ParticleEmitter emitter(maxParticles, emissionRate, speed, speedOffset, angle, angleOffset);

    emitter.setPosition(400, 300);

    float deltaTime = 0.1f;
    bool running = true;

    while (running) {
        app.handleEvents(running);
        emitter.update(deltaTime);

        app.clearScreen();

        //render particles using the drawSquare method
        const std::vector<Particle>& particles = emitter.getParticles();
        for (std::size_t i = 0; i < particles.size(); ++i) {
            app.drawSquare(particles[i].position.x, particles[i].position.y, 5);
        }

        app.presentScreen();

        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }

    app.cleanUp();
    return 0;
}
