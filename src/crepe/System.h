#pragma once

namespace crepe {

class System {
public:
	static System & get_instance();
	virtual void update() = 0;

protected:
	System() { };
	virtual ~System() { };

private:
	// singleton
	System(const System &) = delete;
	System(System &&) = delete;
	System & operator=(const System &) = delete;
	System & operator=(System &&) = delete;
};

}

