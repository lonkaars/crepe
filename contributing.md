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

```cpp
code-style-example/style.h
```

```cpp
code-style-example/style.cpp
```

```cpp
// good
class MyClass
{
public:
  void do_something(const int i);
  void do_something(const std::string &str);
};
```

```cpp
// instead of doing this
auto s = "Hello";
auto x = "42"s;
auto x = 42;
auto x = 42.f;

// Do this
std::string s = "Hello";
std::string  x = "42"s;
int x = 42;
float x = 42.f;
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

