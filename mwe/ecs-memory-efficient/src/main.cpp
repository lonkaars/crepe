#include <iostream>
#include <vector>
#include <cstdint>

#include "ComponentManager.h"
#include "GameObjectMax.h"
#include "Components.h"

int main() {
	GameObject gameObect0(0, "Name: 0", "Tag: 0", 0);	//Entity 0
	GameObject gameObect1(1, "Name: 1", "Tag: 1", 1);	//Entity 1
	GameObject gameObect2(2, "Name: 2", "Tag: 2", 2);	//Entity 2
	GameObject gameObect3(3, "Name: 3", "Tag: 3", 3);	//Entity 3
	GameObject gameObect4(4, "Name: 4", "Tag: 4", 4);	//Entity 4
	GameObject gameObect5(5, "Name: 5", "Tag: 5", 5);	//Entity 5
	GameObject gameObect6(6, "Name: 6", "Tag: 6", 6);	//Entity 6
	GameObject gameObect7(7, "Name: 7", "Tag: 7", 7);	//Entity 7

	gameObect0.AddComponent<Sprite>("C:/object0");	//Add a sprite to entity0
	gameObect0.AddComponent<Rigidbody>(1, 2, 3);	//Also add a rigidbody to entity0
	gameObect0.AddComponent<Rigidbody>(3, 2, 1);	//Add a second rigidbody to entity0

	gameObect1.AddComponent<Rigidbody>(4, 5, 6);	//Only add a rigidbody to entity1

	gameObect2.AddComponent<Sprite>("C:/object2/1");	//Add four sprites to entity2
	gameObect2.AddComponent<Sprite>("C:/object2/2");
	gameObect2.AddComponent<Sprite>("C:/object2/3");
	gameObect2.AddComponent<Sprite>("C:/object2/4");
	gameObect2.AddComponent<Rigidbody>(10, 100, 500);	//Add four rigidbodies to entity2
	gameObect2.AddComponent<Rigidbody>(10, 100, 501);
	gameObect2.AddComponent<Rigidbody>(10, 100, 502);
	gameObect2.AddComponent<Rigidbody>(10, 100, 500);
	
	//Add non components to entity3, entity4, entity5 and entity6

	gameObect7.AddComponent<Sprite>("C:/object7");	//Add a sprite to entity 7
	gameObect7.AddComponent<Colider>(30);	//Add a colder to entity 7

	//The entities are now initialized
	//Now I will demonstrate some ways of retreiving/getting components

	std::cout << "Finding all sprites of entity 0" << std::endl;
	std::vector<std::reference_wrapper<Sprite>> spriteOfEntity0 = ComponentManager::GetInstance().GetComponentsByID<Sprite>(gameObect0.mId);
	for(Sprite& spriteEntity0 : spriteOfEntity0) {
		std::cout << "Sprite of entity 0: " << spriteEntity0.mPath << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Finding all rigidbodies of entity 0" << std::endl;
	std::vector<std::reference_wrapper<Rigidbody>> rigidbodyOfEntity0 = ComponentManager::GetInstance().GetComponentsByID<Rigidbody>(gameObect0.mId);
	for(Rigidbody& rigidbodyEntity0 : rigidbodyOfEntity0) {
		std::cout << "Rigidbody of entity 0: " << rigidbodyEntity0.mMass << " " << rigidbodyEntity0.mGravityScale << " " << rigidbodyEntity0.mBodyType << std::endl;

		rigidbodyEntity0.mMass = 15;
	}
	std::cout << std::endl;

	std::cout << "Finding all coliders of entity 0" << std::endl;
	std::vector<std::reference_wrapper<Colider>> coliderOfEntity0 = ComponentManager::GetInstance().GetComponentsByID<Colider>(gameObect0.mId);
	for(Colider& coliderEntity0 : coliderOfEntity0) {
		std::cout << "Colider of entity 0: " << coliderEntity0.mSize << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Finding all sprites of entity 3" << std::endl;
	std::vector<std::reference_wrapper<Sprite>> spriteOfEntity3 = ComponentManager::GetInstance().GetComponentsByID<Sprite>(gameObect3.mId);
	for(Sprite& spriteEntity3 : spriteOfEntity3) {
		std::cout << "Sprite of entity 3: " << spriteEntity3.mPath << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Finding all rigidbodies of entity 3" << std::endl;
	std::vector<std::reference_wrapper<Rigidbody>> rigidbodyOfEntity3 = ComponentManager::GetInstance().GetComponentsByID<Rigidbody>(gameObect3.mId);
	for(Rigidbody& rigidbodyEntity3 : rigidbodyOfEntity3) {
		std::cout << "Rigidbody of entity 3: " << rigidbodyEntity3.mMass << " " << rigidbodyEntity3.mGravityScale << " " << rigidbodyEntity3.mBodyType << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Finding all sprites of all entities" << std::endl;
	std::vector<std::pair<std::reference_wrapper<Sprite>, std::uint32_t>> sprites = ComponentManager::GetInstance().GetComponentsByType<Sprite>();
	for(auto& [sprite, id] : sprites) {
		std::cout << "Sprite of id: " << id << ": " << sprite.get().mPath << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Finding all coliders of all entities" << std::endl;
	std::vector<std::pair<std::reference_wrapper<Colider>, std::uint32_t>> coliders = ComponentManager::GetInstance().GetComponentsByType<Colider>();
	for(auto& [colider, id] : coliders) {
		std::cout << "Colder of id: " << id << ": " << colider.get().mSize << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Finding all rigidbodies of all entities" << std::endl;
	std::vector<std::pair<std::reference_wrapper<Rigidbody>, std::uint32_t>> rigidBodies = ComponentManager::GetInstance().GetComponentsByType<Rigidbody>();
	for(auto& [rigidbody, id] : rigidBodies) {
		std::cout << "Rigidbody of id: " << id << ": " << rigidbody.get().mMass << " " << rigidbody.get().mGravityScale << " " << rigidbody.get().mBodyType << std::endl;

		rigidbody.get().mMass = -1;
	}
	std::cout << std::endl;

	std::cout << "Finding all rigidbodies of all entities for the second time (after changing mMass to -1)" << std::endl;
	std::vector<std::pair<std::reference_wrapper<Rigidbody>, std::uint32_t>> rigidBodies2 = ComponentManager::GetInstance().GetComponentsByType<Rigidbody>();
	for(auto& [rigidbody2, id2] : rigidBodies2) {
		std::cout << "Rigidbody of id: " << id2 << ": " << rigidbody2.get().mMass << " " << rigidbody2.get().mGravityScale << " " << rigidbody2.get().mBodyType << std::endl;
	}
	std::cout << std::endl;
}
