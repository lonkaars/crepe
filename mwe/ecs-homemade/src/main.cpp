#include <iostream>
#include <vector>
#include <cstdint>

#include "ComponentManager.h"
#include "GameObjectMax.h"
#include "Components.h"

int main() {
	GameObject gameObect0(0, "Name: 0", "Tag: 0", 0);	//Entity 0
	GameObject gameObect1(1, "Name: 1", "Tag: 1", 1);	//Entity 1

	//Sprite sprite0;
	//Rigidbody rigidbody0(1, 2, 3);
	gameObect0.AddComponent<Sprite>();			//Add a sprite to entity0
	gameObect0.AddComponent<Rigidbody>(1, 2, 3);	//Also add a rigidbody to entity0
	gameObect0.AddComponent<Rigidbody>(3, 2, 1);	//Add a second rigidbody to entity0

	//Rigidbody rigidbody1(4, 5, 6);
	gameObect1.AddComponent<Rigidbody>(4, 5, 6);	//Only add a rigidbody to entity1

	//The entities are now initialized
	//Now I will demonstrate some ways of retreiving/getting components

	std::vector<std::reference_wrapper<Rigidbody>> rigidbodyOfEntity0 = ComponentManager::GetInstance().GetComponentsByID<Rigidbody>(gameObect0.mId);			//Get the pointer to the Rigidbody component of entity 0
	for(Rigidbody& rigidbodyEntity0 : rigidbodyOfEntity0) {
		std::cout << "rigidbodyOfEntity0: " << rigidbodyEntity0.mMass << " " << rigidbodyEntity0.mGravityScale << " " << rigidbodyEntity0.mBodyType << std::endl;
		std::cout << std::endl;
	}

	std::vector<std::pair<std::reference_wrapper<Rigidbody>, std::uint32_t>> rigidBodies = ComponentManager::GetInstance().GetComponentsByType<Rigidbody>();
	for(auto& [rigidbody, id] : rigidBodies) {
		std::cout << "Rigidbody of id: " << id << ": " << rigidbody.get().mMass << " " << rigidbody.get().mGravityScale << " " << rigidbody.get().mBodyType << std::endl;
	}
}
