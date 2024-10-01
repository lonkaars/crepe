#include "Transform.hpp"

void Transform::SetPosition(float x, float y) {
    
    position[0] = x;
    position[1] = y;
}

void Transform::SetScale(float x, float y) {
    scale[0] = x;
    scale[1] = y;
}