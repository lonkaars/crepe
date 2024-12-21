#pragma once

#include <crepe/api/Script.h>

class ButtonStartScript : public crepe::Script {
public:
	void init() override;
	void frame_update(crepe::duration_t delta_time) override;
	bool on_button_press(const crepe::ButtonPressEvent& e);
	bool on_button_enter(const crepe::ButtonEnterEvent& e);
	bool on_button_exit(const crepe::ButtonExitEvent& e);
private:
 	bool transition = false;
	static constexpr float SLOW_DOWN = 200;
	static constexpr float END = 300;
	const float velocity_max = 200;
	const float velocity_step = 200;
	float velocity = 20;
};
