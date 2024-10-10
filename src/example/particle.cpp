#include <iostream>
#include <thread>
#include <chrono>
#include "SDLApp.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"
#include "Particle.h"
#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/GameObject.h>
#include <chrono>

using namespace crepe;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char* argv[]) {
    SDLApp app(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!app.initialize()) {
        cerr << "Failed to initialize SDLApp." << endl;
        return 1;
    }

	auto & mgr = ComponentManager::get_instance();
	GameObject * game_object[1];
	game_object[0] = new GameObject(0, "Name", "Tag", 0);
	

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
    // vector<ParticleEmitter> emitters;
	game_object[0]->add_component<ParticleEmitter>(maxParticles, emissionRate, speed, speedOffset, angle, angleOffset, beginLifespan, endLifespan);

	std::vector<std::reference_wrapper<ParticleEmitter>> emitters = mgr.get_components_by_type<ParticleEmitter>();
	

    // Loop to create 1000 emitters
    // for (unsigned int i = 0; i < 1000; ++i) {
    //     ParticleEmitter emitter(maxParticles, emissionRate, speed, speedOffset, angle, angleOffset, beginLifespan, endLifespan);
        
    //     // Set a position for each emitter, modifying the position for demonstration
    //     emitter.m_position = {static_cast<float>(200 + (i % 100)), static_cast<float>(200 + (i / 100) * 10)}; // Adjust position for each emitter
        
    //     emitters.push_back(emitter); // Add the emitter to the vector
    // }
    float deltaTime = 0.1f;
    bool running = true;
    cout << "start loop " << endl;
    while (running) {
        app.handleEvents(running);

        // Start timing
        auto start = chrono::high_resolution_clock::now();

        particleSystem.update(deltaTime, emitters); // update particle system with delta time and emitters

        // End timing
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<float, milli> duration = end - start; // get duration in milliseconds

        cout << "Update took " << duration.count() << " ms" << endl;
        app.clearScreen();

        start = chrono::high_resolution_clock::now();
        // render particles using the drawSquare method from SDLApp
        for (const ParticleEmitter& emitter : emitters) {
            for (const Particle& particle : emitter.particles) {
                if(particle.active)app.drawSquare(particle.position.x, particle.position.y, 5); // draw each particle
            }
        }
        

        app.presentScreen();
        end = chrono::high_resolution_clock::now();
         duration = end - start; // get duration in milliseconds

        cout << "screen took " << duration.count() << " ms" << endl;

        this_thread::sleep_for(chrono::milliseconds(20)); // simulate ~50 FPS
    }

    app.cleanUp();
    return 0;
}
