#pragma once

#include <vector>
#include "api/ParticleEmitter.h"


namespace crepe {

class ParticleSystem {
public:
    ParticleSystem();
    void update();
private:
    void emitParticle(ParticleEmitter &emitter); //emits a new particle

    float m_elapsedTime; //elapsed time since the last emission
};

}
