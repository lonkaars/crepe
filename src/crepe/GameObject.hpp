#pragma once

#include "Component.hpp"
#include <vector>

class GameObject {
public:
    std::vector<Component*> components;

    void AddComponent(Component* component);
    void UpdateComponents();

    virtual void Draw() = 0;
};
