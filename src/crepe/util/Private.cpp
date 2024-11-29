#include "Private.h"

using namespace crepe;

bool Private::empty() const noexcept {
	return this->instance == nullptr;
}

Private::~Private() {
	if (this->instance == nullptr) return;
	this->destructor(this->instance);
}

Private::Private(Private && other) {
	*this = std::move(other);
}

Private & Private::operator=(Private && other) {
	// TODO: ideally this function checks for self-assignment
	this->instance = other.instance;
	this->destructor = other.destructor;
	this->type = other.type;

	other.instance = nullptr;
	other.destructor = [](void*){};

	return *this;
}

