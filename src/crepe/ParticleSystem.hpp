#pragma once

#include <vector>
#include "ParticleEmitter.hpp"

class ParticleSystem {
public:
    ParticleSystem();
    void update(float deltaTime, std::vector<ParticleEmitter>& emitters);
private:
    void emitParticle(ParticleEmitter &emitter); //emits a new particle

    float m_elapsedTime; //elapsed time since the last emission
};
