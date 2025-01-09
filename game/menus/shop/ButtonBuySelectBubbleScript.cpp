#include "ButtonBuySelectBubbleScript.h"
#include "../MenusConfig.h"
#include "Config.h"
#include "ValueBroker.h"
#include "manager/SaveManager.h"
#include "menus/shop/Shopconfig.h"

using namespace crepe;
using namespace std;

void ButtonBuySelectBubbleScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool ButtonBuySelectBubbleScript::on_button_press(const ButtonPressEvent & e) {
	SaveManager & save = this->get_save_manager();
	ValueBroker<int> buy_bullet = save.get<int>(BUY_BUBBLE_SAVE,0);
	if(!buy_bullet.get()){
		ValueBroker<int> coins = save.get<int>(TOTAL_COINS_GAME,0);
		if(coins.get() >= 1000)
		{
			int coin = coins.get();
			coin -= 1000;
			save.set(TOTAL_COINS_GAME,coin);
			save.set(BUY_BUBBLE_SAVE,1);
		}
	}
	else {
		save.set(JETPACK_PARTICLES,1);
	}
	this->trigger_event<ShopUpdate>();
	return false;
}
