#include <iostream>
#include <vector>
#include <cstdint>

#include "ComponentManager.h"
#include "GameObjectMax.h"
#include "Components.h"

int main() {
	GameObject gameObect0(0, "Name: 0", "Tag: 0", 0);	//Entity 0
	GameObject gameObect1(1, "Name: 1", "Tag: 1", 1);	//Entity 1

	Sprite sprite0;
	Rigidbody rigidbody0(1, 2, 3);
	gameObect0.AddComponent<Sprite>(&sprite0);			//Add a sprite to entity0
	gameObect0.AddComponent<Rigidbody>(&rigidbody0);	//Also add a rigidbody to entity0

	Rigidbody rigidbody1(4, 5, 6);
	gameObect1.AddComponent<Rigidbody>(&rigidbody1);	//Only add a rigidbody to entity1

	//The entities are now initialized
	//Now I will demonstrate some ways of retreiving/getting components

	Rigidbody* rigidbodyOfEntity0 = ComponentManager::GetInstance().GetComponent<Rigidbody>(gameObect0.mId);			//Get the pointer to the Rigidbody component of entity 0
	std::cout << "rigidbodyOfEntity0: " << rigidbodyOfEntity0->mMass << " " << rigidbodyOfEntity0->mGravityScale << " " << rigidbodyOfEntity0->mBodyType << std::endl;
	std::cout << std::endl;

	std::vector<std::uint32_t> rigidbodyIDs = ComponentManager::GetInstance().GetAllComponentIDs<Rigidbody>();			//Get all the IDs that have a Rigidbody component
	for(std::uint32_t ID : rigidbodyIDs) {
		std::cout << "Rigidbody ID: " << ID << std::endl;
	}
	std::cout << std::endl;

	std::vector<Rigidbody*> rigidbodyComponents = ComponentManager::GetInstance().GetAllComponentPointer<Rigidbody>();	//Get all the pointers to the Rigidbody component(s)
	for(Rigidbody* rigidbody : rigidbodyComponents) {
		std::cout << "rigidbody: " << rigidbody->mMass << " " << rigidbody->mGravityScale << " " << rigidbody->mBodyType << std::endl;
	}
	std::cout << std::endl;
}
