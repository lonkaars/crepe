#include "Exception.h"

using namespace crepe;
using namespace std;

const char * Exception::what() const noexcept { return error.c_str(); }

Exception::Exception(const string & msg) {
	this->error = msg;
}

