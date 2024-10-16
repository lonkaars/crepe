#include "Components.h"
#include <iostream>

template <typename T>
BehaviourWrapper<T>::BehaviourWrapper() : instance() {}

template <typename T>
void BehaviourWrapper<T>::onStart() {
	instance.onStart();
}

template <typename T>
void BehaviourWrapper<T>::onUpdate() {
	instance.onUpdate();
}

template <typename T>
void BehaviourScript::addScript() {
	behaviour = std::make_unique<BehaviourWrapper<T>>();
}
