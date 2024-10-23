

#include "style.h"

MyClass::MyClass(int t_value) : m_value(t_value) {}

MyClass::MyClass() { m_value = 0; }

MyClass::~MyClass() {}

const int MyClass::get_value() const { return m_value; }

void MyClass::set_value(const int t_value) { m_value = t_value; }

void MyClass::increment() { m_value += 1; }
