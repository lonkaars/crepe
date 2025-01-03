#pragma once

#include "api/Script.h"

class CoinScript : public crepe::Script {
public:
	void init() override;
	bool on_collision(const crepe::CollisionEvent & collisionData);
	static constexpr const char* PLAYER_NAME = "player";
	static constexpr const char* COIN_GAME_AMOUNT = "coin_game_amount";
};
