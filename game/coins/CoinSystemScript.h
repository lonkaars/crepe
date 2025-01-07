#pragma once

#include <string>
#include <random>

#include <crepe/types.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>

class CoinSystemScript : public crepe::Script {
private:
	struct CoinData{
		crepe::vec2 start_location = {0,0};
		std::string name = "";
		bool active = false;
		CoinData(crepe::vec2 start_location) : start_location(start_location),name(""), active(false) {}
	};
public:
	CoinSystemScript() {};
	void init() override;
	void frame_update(crepe::duration_t dt) override;
private:
	void add_location(const crepe::vec2& location);
	void despawn_coins();
	void spawn_coins();
	void generate_locations();
	float preset_1(const crepe::vec2 & begin_position);
	float preset_2(const crepe::vec2 & begin_position);
	float preset_3(const crepe::vec2 & begin_position);
	float preset_4(const crepe::vec2 & begin_position);
	float preset_5(const crepe::vec2 & begin_position);
private:
	std::vector<std::function<float(const crepe::vec2&)>> functions = {
		[this](const crepe::vec2& pos) { return preset_1(pos); },
		[this](const crepe::vec2& pos) { return preset_2(pos); },
		[this](const crepe::vec2& pos) { return preset_3(pos); },
		[this](const crepe::vec2& pos) { return preset_4(pos); },
		[this](const crepe::vec2& pos) { return preset_5(pos); }
	};
	std::vector<int> weights = {20, 20,20,20, 20};
	std::random_device rd;
	std::default_random_engine engine;
	float system_position = 1400;
	static constexpr float SYSTEM_POSITION_OFFSET = 200;
private:
	static constexpr float SPAWN_SPACING_MIN = 400;
	static constexpr float SPAWN_SPACING_MAX = 1000;
	static constexpr float SPAWN_DISTANCE = 600;
	static constexpr float DESPAWN_DISTANCE = 600;
	static constexpr float SPAWN_AREA = 50;
	std::vector<CoinData> coin_locations;
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
// 
//  ********
// **********
//  ********
// 
	static constexpr float ROW_OFFSET_2 = 25;
	static constexpr float COLUM_OFFSET_2 = 25;
	static constexpr int COLUM_AMOUNT_2 = 10;
// preset three settings
// ***
//   
//     ***
// 
//         *** 
	static constexpr float ROW_OFFSET_3 = 100;
	static constexpr float COLUM_OFFSET_3 = 25;
	static constexpr int COLUM_AMOUNT_3 = 3;
// preset four settings
//         ***
//   
//     ***
// 
// *** 
	static constexpr float ROW_OFFSET_4 = 100;
	static constexpr float COLUM_OFFSET_4 = 25;
	static constexpr int COLUM_AMOUNT_4 = 3;
// preset five settings
//
//			***
//	
	static constexpr float ROW_OFFSET_5 = 25;
	static constexpr float COLUM_OFFSET_5 = 25;
	static constexpr int COLUM_AMOUNT_5 = 3;
};
