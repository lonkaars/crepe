#include <chrono>
#include <iostream>
#include <thread>

#include <crepe/Component.h>
#include <crepe/ComponentManager.h>
#include <crepe/Particle.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/ParticleEmitter.h>
#include <crepe/facade/SDLApp.h>
#include <crepe/system/ParticleSystem.h>
#include <crepe/api/Point.h>

using namespace crepe;
using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main(int argc, char * argv[]) {
	SDLApp app(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (!app.initialize()) {
		cerr << "Failed to initialize SDLApp." << endl;
		return 1;
	}

	GameObject * game_object[1];
	game_object[0] = new GameObject(0, "Name", "Tag", Point{0, 0}, 0, 1);

	// FIXME: all systems are singletons, so this shouldn't even compile.
	ParticleSystem particle_system;

	unsigned int max_particles = 100; // maximum number of particles
	unsigned int emission_rate = 10; // particles created per second
	unsigned int speed = 50; // base speed of particles
	unsigned int speed_offset = 10; // random offset for particle speed
	unsigned int angle = 270; // base angle of particle emission
	unsigned int angle_offset = 30; // random offset for particle angle
	float begin_lifespan = 0.0f; // beginning lifespan of particles
	float end_lifespan = 6.0f; // ending lifespan of particles

	// Vector to hold all the emitters
	// vector<ParticleEmitter> emitters;
	game_object[0]->add_component<ParticleEmitter>(
		max_particles, emission_rate, speed, speed_offset, angle, angle_offset,
		begin_lifespan, end_lifespan);

	// Loop to create 1000 emitters
	// for (unsigned int i = 0; i < 1000; ++i) {
	//     ParticleEmitter emitter(maxParticles, emissionRate, speed, speedOffset, angle, angleOffset, beginLifespan, endLifespan);

	//     // Set a position for each emitter, modifying the position for demonstration
	//     emitter.m_position = {static_cast<float>(200 + (i % 100)), static_cast<float>(200 + (i / 100) * 10)}; // Adjust position for each emitter

	//     emitters.push_back(emitter); // Add the emitter to the vector
	// }
	float delta_time = 0.1f;
	bool running = true;
	cout << "start loop " << endl;
	while (running) {
		app.handle_events(running);

		// Start timing
		auto start = chrono::high_resolution_clock::now();

		// POC CODE
		particle_system.update();
		// POC CODE

		// End timing
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float, milli> duration
			= end - start; // get duration in milliseconds

		cout << "Update took " << duration.count() << " ms" << endl;
		app.clear_screen();

		start = chrono::high_resolution_clock::now();
		// render particles using the draw_square method from SDLApp
		ComponentManager & mgr = ComponentManager::get_instance();
		std::vector<std::reference_wrapper<ParticleEmitter>> emitters
			= mgr.get_components_by_type<ParticleEmitter>();
		for (const ParticleEmitter & emitter : emitters) {
			for (const Particle & particle : emitter.particles) {
				if (particle.active)
					app.draw_square(particle.position.x, particle.position.y,
									5); // draw each particle
			}
		}

		app.present_screen();
		end = chrono::high_resolution_clock::now();
		duration = end - start; // get duration in milliseconds

		cout << "screen took " << duration.count() << " ms" << endl;

		this_thread::sleep_for(chrono::milliseconds(20)); // simulate ~50 FPS
	}

	app.clean_up();
	return 0;
}
