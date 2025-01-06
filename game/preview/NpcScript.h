
#include <crepe/api/Script.h>


class NpcScript : public crepe::Script {

private:

public:
	void init();
	void fixed_update(crepe::duration_t dt);

};
