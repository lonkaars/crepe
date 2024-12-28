#pragma once

#include "CoinData.h"
#include "api/CircleCollider.h"
#include "api/Script.h"
#include "api/Sprite.h"
#include "api/Transform.h"

class CoinSystemScript : public crepe::Script {
public:
	CoinSystemScript() {};
	void init() override;
	void frame_update(crepe::duration_t dt) override;
private:
	void add_location(const crepe::vec2& location);
	void despawn_coins();
	void spawn_coins();
	float preset_1(const crepe::vec2 & begin_position);
	float preset_2(const crepe::vec2 & begin_position);
private:
	static constexpr float SPAWN_DISTANCE = 400;
	static constexpr float DESPAWN_DISTANCE = 400;
	static constexpr float SPAWN_AREA = 50;
	static std::vector<CoinData> coin_locations;
private:
// preset one settings
// *****				*****
//
//
//
//				*****				*****
	static constexpr float ROW_OFFSET_1 = 100;
	static constexpr float COLUM_OFFSET_1 = 25;
	static constexpr int COLUM_AMOUNT_1 = 5;
private:
// preset two settings
// *****				*****
//
//
//
//				*****				*****
	static constexpr float ROW_OFFSET_2 = 25;
	static constexpr float COLUM_OFFSET_2 = 25;
	static constexpr int COLUM_AMOUNT_2 = 10;
};
