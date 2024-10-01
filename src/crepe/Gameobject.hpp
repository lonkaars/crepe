#pragma once
#include "Component.hpp"
#include "Transform.hpp"
#include <string>
#include <vector>
#include <memory>

class GameObject {
public:
    GameObject(const std::string& name, const std::string& tag, int layer, 
               float posX = 0.0f, float posY = 0.0f, float rot = 0.0f, 
               float scaleX = 1.0f, float scaleY = 1.0f)
        : name(name), tag(tag), active(true), layer(layer), 
          transform(posX, posY, rot, scaleX, scaleY) {}

    void AddComponent(Component* component) {
        components.push_back(component);
    }

    bool IsActiveInWorld();
    bool IsActive();

    std::string name;
    std::string tag;
    bool active;
    int layer;
    Transform transform;
    std::vector<Component*> components; // This holds all components (RigidBody, etc.)
};
