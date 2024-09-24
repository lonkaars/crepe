#include "GameObject.hpp"

void GameObject::AddComponent(Component* component) {
    components.push_back(component);
}

void GameObject::UpdateComponents() {
    for (Component* component : components) {
        component->Update();
    }
}
