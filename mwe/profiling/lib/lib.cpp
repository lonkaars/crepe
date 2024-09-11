#include <chrono>
#include <thread>
#include <random>

#include "lib.h"

// yeah this is bad, boo hoo
using namespace std;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<mt19937::result_type> random_dist(1, 50);

static void random_slow() {
	int delay = random_dist(rng);
	sleep_for(milliseconds(delay));
}

int recursive(int rem) {
	if (rem <= 0) return 0;
	random_slow();
	return recursive(rem - 1) + recursive(rem - 2);
}

