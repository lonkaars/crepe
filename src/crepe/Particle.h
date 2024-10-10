#pragma once

namespace crepe {

struct Position {
        float x;
        float y;
    };

class Particle {
public:

    Position position;
    Position velocity;
    float lifespan;
    bool active;

    Particle();
    void reset(float lifespan, Position position, Position velocity);
    void update(float deltaTime);
    float timeInLife;
};

}
