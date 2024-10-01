#pragma once

class Particle {
public:
    struct Position {
        int x;
        int y;
    };

    Position position;
    Position velocity;
    float lifespan;

    Particle(float lifespan, Position position, Position velocity);
    void update(float deltaTime);
    bool isAlive() const;
private:
    float timeInLife;
};
