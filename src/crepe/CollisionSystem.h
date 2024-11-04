#pragma once
#include "api/BoxCollider.h"
#include "api/CircleCollider.h"
#include "api/Transform.h"
#include "api/Rigidbody.h"

#include <vector>
#include <utility>
#include "api/event.h"
#include "api/eventManager.h"


namespace crepe {

class CollisionSystem {
public:
	CollisionSystem();
	void update();
private:
	// bool checkAABBCollision(const crepe::api::BoxCollider& box1,const crepe::api::Transform& trf1, const crepe::api::Rigidbody& rgb1, 
	// const crepe::api::BoxCollider& box2, const crepe::api::Transform& trf2, const crepe::api::Rigidbody& rgb2);

	// void detectBoxCollisions(std::vector<std::pair<int, int>>& collisions);
	// void handleCollision(std::vector<std::pair<int, int>> &collisions);
};

} // namespace crepe
