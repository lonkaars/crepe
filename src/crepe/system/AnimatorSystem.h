#pragma once

#include "System.h"
namespace crepe {

class AnimatorSystem : public System { 

public:

	static AnimatorSystem & get_instance();
	void update() override;

private:
	AnimatorSystem();
	~AnimatorSystem();

};

} // namespace crepe
