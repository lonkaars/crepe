#pragma once
#include "api/Event.h"

//tags
static constexpr const char * BUY_BULLET = "BUY_BULLET";
static constexpr const char * SELECT_BULLET = "SELECT_BULLET";
static constexpr const char * BUY_BUBBLE = "BUY_BUBBLE";
static constexpr const char * SELECT_BUBBLE = "SELECT_BUBBLE";

//save_data
static constexpr const char * BUY_BULLET_SAVE = "BUY_BULLET_SAVE";
static constexpr const char * BUY_BUBBLE_SAVE = "BUY_BUBBLE_SAVE";

struct ShopUpdate : public crepe::Event {};
