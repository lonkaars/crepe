#include <cstdlib>

#include "Random.h"

float Random::f(float upper, float lower) {
	float range = upper - lower;
	float x = ((float) rand() / (float) (RAND_MAX)) * range;
	return x + lower;
}

double Random::d(double upper, double lower) {
	double range = upper - lower;
	double x = ((double) rand() / (double) (RAND_MAX)) * range;
	return x + lower;
}

int Random::i(int upper, int lower) {
	int range = upper - lower;
	int x = rand() % range;
	return x + lower;
}

unsigned Random::u(unsigned upper, unsigned lower) {
	unsigned range = upper - lower;
	unsigned x = rand() % range;
	return x + lower;
}

bool Random::b() {
	return rand() % 2;
}

