#pragma once

class Particle {
public:
    struct Position {
        float x;
        float y;
    };

    Position position;
    Position velocity;
    float lifespan;

    Particle(float lifespan, Position position, Position velocity);
    void update(float deltaTime);
    bool isAlive() const;
    float timeInLife;
};
