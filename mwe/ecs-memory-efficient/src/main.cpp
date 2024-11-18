#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "ComponentManager.h"
#include "Components.h"
#include "GameObjectMax.h"

int main() {
	auto startAdding = std::chrono::high_resolution_clock::now();

	GameObject * gameObject[100000];

	for (int i = 0; i < 100000; ++i) {
		gameObject[i] = new GameObject(i, "Name", "Tag", 0);

		gameObject[i]->addSpriteComponent("C:/Test");
		gameObject[i]->addRigidbodyComponent(0, 0, i);
		gameObject[i]->addColiderComponent(i);
	}

	auto stopAdding = std::chrono::high_resolution_clock::now();

	//This is what systems would do:

	std::vector<std::reference_wrapper<Sprite>> allSprites
		= ComponentManager::GetInstance().getAllSpriteReferences();
	for (Sprite & sprite : allSprites) {
		//std::cout << sprite.mPath << std::endl;
	}
	//std::cout << std::endl;

	std::vector<std::reference_wrapper<Rigidbody>> allRigidbody
		= ComponentManager::GetInstance().getAllRigidbodyReferences();
	for (Rigidbody & rigidbody : allRigidbody) {
		//std::cout << rigidbody.mMass << " " << rigidbody.mGravityScale << " " << rigidbody.mBodyType << std::endl;
	}
	//std::cout << std::endl;

	std::vector<std::reference_wrapper<Colider>> allColider
		= ComponentManager::GetInstance().getAllColiderReferences();
	for (Colider & colider : allColider) {
		//std::cout << colider.mSize << std::endl;
	}

	auto stopLooping = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < 100000; ++i) {
		delete gameObject[i];
	}

	auto Addtime
		= std::chrono::duration_cast<std::chrono::microseconds>(stopAdding - startAdding);
	auto LoopTime
		= std::chrono::duration_cast<std::chrono::microseconds>(stopLooping - stopAdding);
	std::cout << "AddTime: " << Addtime.count() << " us" << std::endl;
	std::cout << "LoopTime: " << LoopTime.count() << " us" << std::endl;
}
