#include <stdexcept>

#include "SignalCatch.h"

using namespace crepe;
using namespace std;

SignalCatch::SignalCatch() {
	segvcatch::init_segv(&SignalCatch::segv);
	segvcatch::init_fpe(&SignalCatch::fpe);
}

SignalCatch::~SignalCatch() {
	segvcatch::init_segv();
	segvcatch::init_fpe();
}

void SignalCatch::segv() { throw runtime_error("segmentation fault"); }

void SignalCatch::fpe() { throw domain_error("floating point exception"); }
