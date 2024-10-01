#pragma once

#include <vector>
#include <cstdlib>  
#include <ctime>   
#include "Particle.hpp"
#include <cmath>

class ParticleEmitter {
public:
    std::vector<Particle> particles;

    struct Position {
        int x;
        int y;
    } position;

    int maxParticles;
    float emissionRate;
    float elapsedTime;

    ParticleEmitter(int maxParticles, float emissionRate);
    void update(float deltaTime);

private:
    void emitParticle();
    float randFloat(float minangle, float maxangle, float minVel, float maxVel);
};
