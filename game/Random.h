#pragma once

class Random {
public:
	static float f(float upper = 1.0, float lower = 0.0);
	static double d(double upper = 1.0, double lower = 0.0);
	static int i(int upper, int lower = 0);
	static unsigned u(unsigned upper, unsigned lower = 0);

};

