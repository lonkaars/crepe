#pragma once

namespace crepe::api {

class LoopManager {
public:
	LoopManager();
	void setup();
	void loop();
	void setRunning(bool running);

private:
	void processInput();
	void update();
	void lateUpdate();
	void fixedUpdate();
	void render();
	bool gameRunning = false;
	int timeScale = 1;
	float accumulator = 0.0;
	double currentTime;
	double t = 0.0;
	double dt = 0.01;
};

}
