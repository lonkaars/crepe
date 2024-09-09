# Contributing new code

- Please do the following *before* sending a pull request:
  - Merge upstream code (if any) back into your own branch
  - Run formatters/linters

# Git

- Push as often as possible
- Development is done on separate branches, these follow a pattern of
  `name/feature` (i.e. `loek/dll-so-poc` or `jaro/class2`)
- The master branch is considered stable, and should always contain a
  working/compiling version of the project

- TODO: tagging / versions


# Code style

- Formatting nitty-gritty is handled by clang-format/clang-tidy
- ASCII only
- When using libraries of which the header include order is important, make
  sure to separate the include statements using a blank line (clang-format may
  sort include statements, but does not sort across empty lines).
- [Cpp practices](https://lefticus.gitbooks.io/cpp-best-practices/content/)
- [C++ core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Google c++ style](https://google.github.io/styleguide/cppguide.html)


- .h basic code style with doxygen
```cpp
// code-style-example/style.cpp
/*! @file MyClass.h */

#ifndef MYPROJECT_MYCLASS_HPP
#define MYPROJECT_MYCLASS_HPP

/**
 * @brief example class
 */
class MyClass {

public:
	/**
	 * @brief example constructor
	 *
	 * @param[integer] t_value example first argument
	 */
	MyClass(int t_value);

	/**
	 * @brief constructor example
	 *
	 */
	MyClass();

	/**
	 * @brief deconstuctor example
	 *
	 */
	~MyClass();

	/**
	 * @brief setter example with correct const implementation
	 *
	 * @param[const integer] t_value first argument
	 */
	void set_value(const int t_value);

	/**
	 * @brief getter example with correct const implementation
	 *
	 * @return const integer
	 */
	const int get_value() const;

	/**
	 * @brief increment member m_value
	 *
	 */
	void increment();

private:
	/**
	 * @m_value basic member example
	 */
	int m_value;
};

#endif
```

- .cpp basic code style
```cpp
// code-style-example/style.cpp

#include "style.h"

MyClass::MyClass(int t_value) : m_value(t_value) {}

MyClass::MyClass() { m_value = 0; }

MyClass::~MyClass() {}

const int MyClass::get_value() const { return m_value; }

void MyClass::set_value(const int t_value) { m_value = t_value; }

void MyClass::increment() { m_value += 1; }
```

- when to use references

-- If the input parameter in the function cannot accept a nullptr
```cpp
void foo::function(const std::string& name){};
```
-- Use a reference when you know that the object will exist for the lifetime of the reference and when nullability is not a concern.
```cpp
int x = 10;
int& ref = x;
ref = 20;
```

-- If a function should return a reference to an object that exists elsewhere (such as a member of a class or an element in a container), you can return a reference.
```cpp
container& get_element(std::vector<container>& vec, size_t index){
  return vec[index];
}
```
- When to use pointers

-- Use pointers when dealing with dynamic memory
```cpp
int* ptr = new int(5);
delete ptr;
```

-- Pointers can be nullptr, allowing them to represent "no object." Use pointers when you need to express optional ownership or reference.
```cpp
void foo::function(int* ptr){
  if(ptr){
    // ptr is not null
  }
}
```

-- When dealing with polymorphism.
```cpp
class Base {};
class Derived : public Base {};

Base* obj = new Derived();
obj->function();
```


- Do not use auto

-- Instead of doing this
```cpp
auto s = "Hello";
auto x = "42"s;
auto x = 42;
auto x = 42.f;
```
-- Do this.
```cpp
std::string s = "Hello";
std::string  x = "42"s;
int x = 42;
float x = 42.f;
```
- Do not define constants as define but instead directly declare it.
-- This is wrong.
```cpp
#define PI 3.14159;
```

-- Do this.
```cpp
namespace my_project {
  class Constants {
  public:
    static constexpr double PI = 3.14159;
  };
}
```
- Use enum class instead of using enum only to prevent bugs
```cpp
void Print_color(int color);

enum Web_color { red = 0xFF0000, green = 0x00FF00, blue = 0x0000FF };
enum Product_info { red = 0, purple = 1, blue = 2 };

Web_color webby = Web_color::blue;

// Clearly at least one of these calls is buggy.
Print_color(webby);
Print_color(Product_info::blue);
```
- Instead use an enum class:
```cpp

void Print_color(int color);

enum class Web_color { red = 0xFF0000, green = 0x00FF00, blue = 0x0000FF };
enum class Product_info { red = 0, purple = 1, blue = 2 };

Web_color webby = Web_color::blue;
Print_color(webby);  // Error: cannot convert Web_color to int.
Print_color(Product_info::red);  // Error: cannot convert Product_info to int.

```

- Think about using size_t instead of using int for preventing processor mismatching. This might prevent a bug in the future.
```cpp
std::size_t i = 0; // use this instead of using a int
double x = 0.0;
```
- comment style guide, you can use TODO:, FIXME:, NOTE:, or HACK: as admonitions when needed.

-- Bad example
```cpp
// Draw loading screen.
draw_load_screen();
```
-- Better
```cpp 
// Compute the first 10,000 decimals of Pi.
// FIXME: Don't crash when computing the 1,337th decimal due to `increment`
//        being negative.
```

## CMakeLists specific

- Make sure list arguments (e.g. sources, libraries) given to commands (e.g.
  `target_sources`, `target_link_libraries`) are on separate lines. This makes
  resolving merge conflicts when multiple sources were added by different
  people to the same CMakeLists.txt easier.

## Doxygen style

- [a C-style doxygen example](https://www.cs.cmu.edu/~410/doc/doxygen.html)


# Documentation

- All documentation is written in U.S. English
- [stanford latex style](https://web.stanford.edu/class/ee364b/latex_templates/template_notes.pdf)
- TODO

# Libraries

- External libraries should be included as Git submodules under the `lib/`
  subdirectory
- When adding new submodules, make sure to manually set the `branch` and
  `shallow` options in the [.gitmodules](./.gitmodules) file

