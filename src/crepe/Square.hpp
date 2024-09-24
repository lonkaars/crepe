#pragma once

#include "GameObject.hpp"

class Square : public GameObject {
public:
    float x, y; 
    int width, height;

    Square(float xPos, float yPos, int w, int h);

    void Draw() override;
};
