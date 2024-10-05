#include <iostream>
#include <vector>
#include <cstdint>
#include <chrono>

#include "ComponentManager.h"
#include "GameObjectMax.h"
#include "Components.h"

int main() {
	auto startAdding = std::chrono::high_resolution_clock::now();

	GameObject* gameObject[100000];

	for(int i = 0; i < 100000; ++i) {
		gameObject[i] = new GameObject(i, "Name", "Tag", 0);

		gameObject[i]->AddComponent<Sprite>("C:/Test");
		gameObject[i]->AddComponent<Rigidbody>(0, 0, i);
		gameObject[i]->AddComponent<Colider>(i);
	}
	
	auto stopAdding = std::chrono::high_resolution_clock::now();

	//This is what systems would do:

	std::vector<std::pair<std::reference_wrapper<Sprite>, std::uint32_t>> sprites = ComponentManager::GetInstance().GetComponentsByType<Sprite>();
	for(auto& [sprite, id] : sprites) {
		std::cout << sprite.get().mPath << std::endl;
	}
	std::cout << std::endl;

	std::vector<std::pair<std::reference_wrapper<Rigidbody>, std::uint32_t>> rigidBodies = ComponentManager::GetInstance().GetComponentsByType<Rigidbody>();
	for(auto& [rigidbody, id] : rigidBodies) {
		std::cout << rigidbody.get().mMass << " " << rigidbody.get().mGravityScale << " " << rigidbody.get().mBodyType << std::endl;
	}

	std::vector<std::pair<std::reference_wrapper<Colider>, std::uint32_t>> coliders = ComponentManager::GetInstance().GetComponentsByType<Colider>();
	for(auto& [colider, id] : coliders) {
		std::cout << colider.get().mSize << std::endl;
	}
	std::cout << std::endl;

	auto stopLooping = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100000; ++i) {
    	delete gameObject[i];
	}

	auto Addtime = std::chrono::duration_cast<std::chrono::microseconds>(stopAdding - startAdding);
	auto LoopTime = std::chrono::duration_cast<std::chrono::microseconds>(stopLooping - stopAdding);
	std::cout << "AddTime: " << Addtime.count() << " us" << std::endl;
	std::cout << "LoopTime: " << LoopTime.count() << " us" << std::endl;
}
