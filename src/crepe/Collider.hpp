#pragma once

#include "Component.hpp"

class Collider : public Component {
public:
    bool isColliding;

    Collider();

    void Update() override;

    bool CheckCollision(float x1, float y1, float width1, float height1, 
                        float x2, float y2, float width2, float height2);
};
