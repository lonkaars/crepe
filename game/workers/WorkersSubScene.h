#pragma once

namespace crepe {
class Scene;
}

class WorkersSubScene {
public:
	WorkersSubScene(crepe::Scene & scn);

private:
	void worker1(crepe::Scene & scn, float start_x, float init_speed);
	void worker2(crepe::Scene & scn, float start_x, float init_speed);
	void worker3(crepe::Scene & scn, float start_x, float init_speed);
	void worker4(crepe::Scene & scn, float start_x, float init_speed);
	void worker5(crepe::Scene & scn, float start_x, float init_speed);
	void worker6(crepe::Scene & scn, float start_x, float init_speed);
	void worker7(crepe::Scene & scn, float start_x, float init_speed);
	void worker8(crepe::Scene & scn, float start_x, float init_speed);
};
