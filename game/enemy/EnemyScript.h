#pragma once

class EnemyScript : public crepe::Script {
	void init() override;
	void update() override;
	void onCollide(const CollisionEvent & collisionData);
};
