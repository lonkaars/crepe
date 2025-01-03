This document contains
<details><summary>
examples
</summary>
that you can click on to open them.
</details>

# Git

- Please do the following *before* sending a pull request:
  - Merge upstream code (if any) back into your own branch
  - Run formatters/linters
- Push as often as possible
- Development is done on separate branches, these follow a pattern of
  `name/feature` (i.e. `loek/dll-so-poc` or `jaro/class2`)
- The master branch is considered stable, and should always contain a
  working/compiling version of the project
- Pull requests for new code include either automated tests for the new code or
  an explanation as to why the code can not (reliably) be tested
- Non-bugfix pull requests must be approved by at least 2 reviewers before being
  merged
- Pull requests should have the following labels (where appropriate)
  |label|meaning|
  |:-:|-|
  |`fix me`|has feedback that should be resolved/discussed by its author|
  |`review me`|needs additional reviewers (minimum of 2 per PR)|
  |`do not review`|is actively being worked on or not ready for feedback|
  |`high priority`|should be worked on before all the others|
  - PRs start with the `review me` label
  - Reviewers—
    - Add the `fix me` label after adding comments
  - Authors—
    - Remove the `review me` label if the pull request has enough reviewers
    - Add the `do not review` label while processing feedback / pushing
      additional commits

<!--
- TODO: tagging / versions
-->

# Code style

- Formatting nitty-gritty is handled by clang-format/clang-tidy (run `make
  format` or `make lint`)
- <details><summary>
  ASCII only
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  // crepe startup message
  std::string message = "Hello, world!";
  ```
  </td><td>

  ```cpp
  // crêpe startup message
  std::string message = "こんにちは世界";
  ```
  </td></tr></table></details>
- <details><summary>
  Class names are always singular
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {};
  ```
  </td><td>

  ```cpp
  class Cars {};
  ```
  </td></tr></table></details>
- Source files (`.cpp`, `.hpp`) contain the following types of comments:
  - What is the code supposed to do (optional)
  - Implementation details (if applicable)
- Header files (`.h`) contain the following types of comments:
  - [Usage documentation](#documentation) (required)
  - Implementation details (if they affect the header)
  - Design/data structure decisions (if applicable)
- <details><summary>
  Comments are placed *above* the line(s) they are explaining
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  int add(int a, int b) {
    // add numbers
    int out = a + b;
    return out;
  }
  ```
  </td><td>

  ```cpp
  int add(int a, int b) {
    int out = a + b; // add numbers
    return out;
  }
  ```
  </td></tr></table></details>
- Header includes (at the top of files) are split into paragraphs separated by
  a blank line. The order is:
  1. system headers (using `<`brackets`>`)
  2. relative headers NOT in the same folder as the current file
  3. relative headers in the same folder as the current file

  > [!NOTE]
  > When using libraries of which the header include order is important, make
  > sure to separate the include statements using a blank line (clang-format
  > may sort include statements, but does not sort across empty lines).

  <details><summary>Example</summary>
  <table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  #include <SDL2/SDL.h>
  #include <iostream>

  #include "api/Sprite.h"
  #include "util/log.h"

  #include "SDLContext.h"
  ```
  </td><td>

  ```cpp
  #include <SDL2/SDL.h>
  #include "SDLContext.h"
  #include "util/log.h"
  #include <iostream>
  #include "api/Sprite.h"
  ```
  </td></tr></table></details>
- <details><summary>
  If there is one, the matching template header (<code>.hpp</code>) is included
  at the bottom of the regular header (<code>.h</code>)
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  Foo.h:
  ```cpp
  #pragma once

  template <typename T>
  void foo();

  #include "Foo.hpp"
  ```

  Foo.hpp:
  ```cpp
  #pragma once
  #include "Foo.h"

  template <typename T>
  void foo() {
    // ...
  }
  ```
  </td><td>

  Foo.h:
  ```cpp
  #pragma once

  template <typename T>
  void foo();
  ```

  Foo.hpp:
  ```cpp
  #pragma once
  #include "Foo.h"

  template <typename T>
  void foo() {
    // ...
  }
  ```
  </td></tr></table></details>
- <details><summary>
  <a href="https://en.cppreference.com/w/cpp/language/using_declaration">Using-declarations</a>
  may not be used in header files (<code>.h</code>, <code>.hpp</code>), only in
  source files (<code>.cpp</code>).
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  example.h:
  ```cpp
  namespace crepe {
  std::string foo();
  }
  ```
  
  </td><td>

  example.h:
  ```cpp
  using namespace std;

  namespace crepe {
  string foo();
  }
  ```
  </td></tr></table></details>

- <details><summary>
  Getter and setter functions are appropriately prefixed with <code>get_</code>
  and <code>set_</code>.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
  public:
    int get_speed() const;
    void set_speed(int speed);
  private:
    int speed;
  };
  
  ```
  </td><td>

  ```cpp
  class Foo {
  public:
    int speed() const;
    void set_speed(int speed);
  private:
    int speed;
  };
  ```
  </td></tr></table></details>
- <details><summary>
  A singleton's instance is always accessed using a getter function that
  instantiates its own class as a static variable within the getter function
  scope, instead of storing the instance as a member variable directly.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
    Foo & get_instance() {
      static Foo instance;
      return instance;
    }
  };
  ```
  </td><td>

  ```cpp
  Foo Foo::instance {};

  class Foo {
    static Foo instance;
    Foo & get_instance() { return Foo::instance; }
  };

  ```
  </td></tr></table></details>
- <details><summary>
  Member variable default values should be directly defined in the class/struct
  declaration instead of using the constructor.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
    int speed = 0;
  };
  
  ```
  </td><td>

  ```cpp
  class Foo {
    Foo() : speed(0) {}
    int speed;
  };
  ```
  </td></tr></table></details>
- Use of the `auto` type is *not* allowed, with the following exceptions:
  - <details><summary>
    When naming the item type in a range-based for loop
    </summary>

    ```cpp
    for (auto & item : foo()) {
      // ...
    }
    ```
    </details>
  - <details><summary>
    When calling template factory methods that explicitly name the return type
    in the function call signature
    </summary>

    ```cpp
    auto ptr = make_unique<Foo>();
    ```
    </details>
  - <details><summary>
    When fetching a singleton instance
    </summary>

    ```cpp
    auto & mgr = crepe::api::Config::get_instance();
    ```
    </details>

- <details><summary>
  Only use member initializer lists for non-trivial types.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
  public:
    Foo() : bar("baz") {}
  private:
    std::string bar;
  };
  
  ```
  </td><td>

  ```cpp
  class Foo {
  public:
    Foo() : bar(0) {}
  private:
    int bar;
  };
  ```
  </td></tr></table></details>
- <details><summary>
  C++-style structs should define default values for all non-trivial fields.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  struct Foo {
    int bar = 0;
    std::string baz;
  };
  ```
  </td><td>

  ```cpp
  struct Foo {
    int bar;
    std::string baz;
  };
  ```
  </td></tr></table></details>
- <details><summary>
  Declare incomplete classes instead of including the relevant header where
  possible (i.e. if you only need a reference or raw pointer).
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Bar;
  class Foo {
    Bar & bar;
  };
  
  ```
  </td><td>

  ```cpp
  #include "Bar.h"
  class Foo {
    Bar & bar;
  };
  ```
  </td></tr></table></details>
- <details><summary>
  Template functions are only <i>declared</i> in a <code>.h</code> header, and
  <i>defined</i> in a matching <code>.hpp</code> header.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  add.h:
  ```cpp
  template <typename T>
  T add(T a, T b);

  #include "add.hpp"
  ```
  
  add.hpp:
  ```cpp
  #include "add.h"

  template <typename T>
  T add(T a, T b) {
    return a + b;
  }
  ```
  </td><td>

  add.h:
  ```cpp
  template <typename T>
  T add(T a, T b) {
    return a + b;
  }
  ```
  </td></tr></table></details>
- <details><summary>
  Where possible, end (initializer) lists with a trailing comma (e.g. with
  structs, enums)
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  enum Color {
    Red,
    Green,
    Blue,
  };
  
  ```
  </td><td>

  ```cpp
  enum Color {
    Red,
    Green,
    Blue
  };
  ```
  </td></tr></table></details>
- <details><summary>
  <code>#pragma</code> should be used instead of include guards
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  #pragma once

  // ...
  ```
  </td><td>

  ```cpp
  #ifndef __INCLUDED_H
  #define __INCLUDED_H

  // ...

  #endif
  ```
  </td></tr></table></details>
- <details><summary>
  Variables that are being moved always use the fully qualified
  <code>std::move</code>
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  using namespace std;
  string foo = "bar";
  ref_fn(std::move(foo));
  ```
  </td><td>

  ```cpp
  using namespace std;
  string foo = "bar";
  ref_fn(move(foo));
  ```
  </td></tr></table></details>
- <details><summary>
  If possible, classes and structs are passed to functions by (const) reference
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  void foo(const Point & p);
  ```
  </td><td>

  ```cpp
  void foo(Point & p);
  void bar(Point p);
  ```
  </td></tr></table></details>
- <details><summary>
  Follow the rule of five
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
  public:
    Foo();
    ~Foo();
    Foo(Foo &&) noexcept;
    Foo & operator = (const Foo &);
    Foo & operator = (Foo &&) noexcept;
  };
  ```
  </td><td>

  ```cpp
  class Foo {
  public:
    Foo();
    ~Foo();
  };
  ```
  </td></tr></table></details>
- <details><summary>
  Ensure const-correctness

  > [!IMPORTANT]
  > C-style APIs that work on (possibly internal) references to structs can be
  > called from const member functions in C++. If the compiler allows you to
  > mark a function as `const` even though it has side effects, it should
  > **not** be marked as `const`.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
  public:
    int get_value() const;
    void set_value(int new_value);
    const std::string & get_name() const;
    void set_name(const std::string & new_name);
  private:
    int value;
    std::string name;
  };
  ```
  </td><td>

  ```cpp
  class Foo {
  public:
    int get_value();
    void set_value(int new_value);
    std::string get_name();
    void set_name(std::string new_name);
  private:
    int value;
    std::string name;
  };
  ```
  </td></tr></table></details>
- <details><summary>
  Files should be named after the class/struct/interface they implement
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  MyClass.h
  MyClass.cpp
  MyClass.hpp
  ```
  </td><td>

  ```cpp
  my_class.h
  myClass.cpp
  my-class.hpp
  ```
  </td></tr></table></details>
- <details><summary>
  Implementations are not allowed in header files, except if the implementation

  - is `= default`
  - is `= delete`
  - is `{}` (empty)
  - only returns a constant literal
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
  public:
    int get_value() const { return 42; }
  };
  ```
  </td><td>

  ```cpp
  class Foo {
  public:
    int calculate_value() const {
      int result = 0;
      // complex calculation
      return result;
    }
  };
  ```
  </td></tr></table></details>
- <details><summary>
  Use angle brackets (<code><></code>) only for including system headers and
  double quotes (<code>""</code>) for including other engine files.

  > [!NOTE]
  > Only files in the examples folder should include engine headers with angle
  > brackets
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  #include <iostream>

  #include "facade/Sound.h"
  ```
  </td><td>

  ```cpp
  #include <iostream>
  #include <crepe/facade/Sound.h>
  ```
  </td></tr></table></details>
- <details><summary>
  Ensure exception safety by using RAII classes
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  auto foo = std::make_unique<Foo>();
  ```
  </td><td>

  ```cpp
  Foo* foo = new Foo();
  // ...
  delete foo;
  ```
  </td></tr></table></details>
- <details><summary>
  Do not use C-style memory management APIs (<code>malloc</code>,
  <code>calloc</code>, <code>free</code>)
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  Foo * foo = new Foo();
  delete foo;
  ```
  </td><td>

  ```cpp
  Foo * foo = (Foo *) malloc(sizeof(Foo));
  free(foo);
  ```
  </td></tr></table></details>
- <details><summary>
  Prefix all class members with <code>this-></code>
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  void Foo::bar() { }

  void Foo::set_value(int value) {
    this->value = value;
    this->bar();
  }
  ```
  </td><td>

  ```cpp
  void Foo::bar() { }

  void Foo::set_value(int new_value) {
    value = new_value;
    bar();
  }
  ```
  </td></tr></table></details>
- <details><summary>
  Assigning booleans should be done with the
  <code>true</code>/<code>false</code> literals instead of
  <code>0</code>/<code>1</code>
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  bool foo = true;
  bool bar = false;
  ```
  </td><td>

  ```cpp
  bool foo = 1;
  bool bar = 0;
  ```
  </td></tr></table></details>
- <details><summary>
  The reason for <code>friend</code> relations are documented
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  //! ComponentManager calls the private constructor of this class
  friend class ComponentManager;
  ```
  </td><td>

  ```cpp
  friend class ComponentManager;
  ```
  </td></tr></table></details>
- <details><summary>
  Do not <i>pick</i> fixed-width integer types (unless required)
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  unsigned long long foo();
  ```
  </td><td>

  ```cpp
  uint64_t foo();
  ```
  </td></tr></table></details>
- <details><summary>
  Utilize standard exceptions where appropriate (those found in <code>&lt;stdexcept&gt;</code>)
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  #include <stdexcept>

  // ...

  if (foo == nullptr) {
    throw std::runtime_error("What is wrong");
  }
  ```
  </td><td>

  ```cpp
  if (foo == nullptr) {
    std::cout << "What is wrong" << std::endl;
    exit(1);
  }
  ```
  </td></tr></table></details>
- <details><summary>
  Mention the name of the class when throwing an exception
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  Foo::bar() {
    if (...)
      throw std::runtime_error("Foo: big error!");
  }
  ```
  </td><td>

  ```cpp
  Foo::bar() {
    if (...)
      throw std::runtime_error("big error!");
  }
  ```
  </td></tr></table></details>
- <details><summary>
  Constructors of classes derived from <code>Component</code> should be
  protected and <code>ComponentManager</code> should be declared as a friend
  class.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class MyComponent : public Component {
  protected:
    MyComponent(...);
    //! Only ComponentManager is allowed to create components
    friend class ComponentManager;
  };
  ```
  </td><td>

  ```cpp
  class MyComponent : public Component {
  public:
    MyComponent(...);
  };
  ```
  </td></tr></table></details>
- <details><summary>
  C++ <code>std::format</code> should be used instead of C-style format specifiers
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  std::string message = std::format("Hello, {}", name);

  dbg_logf("Here too: {}", 3);

  throw std::runtime_error(std::format("Or here: {}", 5));
  ```
  </td><td>

  ```cpp
  char message[50];
  sprintf(message, "Hello, %s", name);
  ```
  </td></tr></table></details>
- <details><summary>
  Argument names should be added in <code>.h</code> files (not only in
  <code>.cpp</code> and <code>.hpp</code> files)
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  Foo.h:
  ```cpp
  void foo(int bar);
  ```

  Foo.cpp:
  ```cpp
  void foo(int bar) {
    // ...
  }
  ```
  </td><td>

  Foo.h:
  ```cpp
  void foo(int);
  ```

  Foo.cpp:
  ```cpp
  void foo(int bar) {
    // ...
  }
  ```
  </td></tr></table></details>
- Do not implement new classes as singletons
- <details><summary>
  Retrieving the first or last indices for iterators with a known or expected
  size should be done using <code>.front()</code> or <code>.back()</code>
  instead of by index
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  vector<int> foo = { 1, 2, 3 };
  int bar = foo.first();
  ```
  </td><td>

  ```cpp
  vector<int> foo = { 1, 2, 3 };
  int bar = foo[0];
  ```
  </td></tr></table></details>
- <details><summary>
  Always explicitly check against <code>NULL</code> (for C APIs) or
  <code>nullptr</code> (for C++ APIs) when checking if a pointer is valid
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  string foo = "Hello world";
  if (foo.c_str() == nullptr)
    // ...

  void * bar = malloc();
  if (bar == NULL)
    // ...
  ```
  </td><td>

  ```cpp
  string foo = "Hello world";
  if (!foo.c_str())
    // ...

  void * bar = malloc();
  if (!bar)
    // ...
  ```
  </td></tr></table></details>

## CMakeLists-specific

- Make sure list arguments (e.g. sources, libraries) given to commands (e.g.
  `target_sources`, `target_link_libraries`) are on separate lines. This makes
  resolving merge conflicts when multiple sources were added by different
  people to the same CMakeLists.txt easier.

## GoogleTest-specific

- Unit tests are not *required* to follow all code standards
- <details><summary>
  Private/protected members may be accessed using preprocessor tricks
  </summary>

  ```cpp
  // include unrelated headers before

  #define private public
  #define protected public

  // headers included after *will* be affected
  ```
  </details>
- Each test source file defines tests within a single test suite (first
  parameter of `TEST()` / `TEST_F()` macro)
- Test source files match their suite name (or test fixture name in the case of
  tests that use a fixture)
- Tests that measure time or use delays must be [disabled][gtest-disable] (by
  prepending `DISABLED_` to the suite or case name).

  These tests will still be compiled, but will only run when the `test_main`
  binary is run with the `--gtest_also_run_disabled_tests` flag.

# Structure

- Files are placed in the appropriate directory:
  |Path|Purpose|
  |-|-|
  |`crepe/`|Auxiliary, managers|
  |`crepe/api/`|User-facing APIs|
  |`crepe/util/`|Standalone utilities and helper functions|
  |`crepe/system/`|(ECS) system classes|
  |`crepe/facade/`|Library façades|
- Do not (indirectly) include private *dependency* headers in API header files,
  as these are no longer accessible when the engine is installed
- All code is implemented under the `crepe` namespace.
- Header files declare either a single class or symbols within a single
  namespace.

# Documentation

[Doxygen commands](https://www.doxygen.nl/manual/commands.html)

- All documentation is written in U.S. English
- <details><summary>
  Doxygen commands are used with a backslash instead of an at-sign.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  /**
   * \brief do something
   *
   * \param bar  Magic number
   */
  void foo(int bar);
  ```
  </td><td>

  ```cpp
  /**
   * @brief do something
   *
   * @param bar  Magic number
   */
  void foo();
  ```
  </td></tr></table></details>
- <details><summary>
  The default constructor and destructor aren't required to have a
  <code>\brief</code> description
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  Foo();
  virtual ~Foo();
  ```
  </td><td>

  ```cpp
  //! Create instance of Foo
  Foo();
  //! Destroy instance of Foo
  virtual ~Foo();
  ```
  </td></tr></table></details>
- <details><summary>
  Parameter direction shouldn't be specified using Doxygen
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  /**
   * \param bar  Reference to Bar
   */
  void foo(const Bar & bar);
  ```
  </td><td>

  ```cpp
  /**
   * \param[in] bar  Reference to Bar
   */
  void foo(const Bar & bar);
  ```
  </td></tr></table></details>
- <details><summary>
  Deleted functions shouldn't have Doxygen comments
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  // singleton
  Foo(const Foo &) = delete;
  Foo(Foo &&) = delete;
  Foo & operator=(const Foo &) = delete;
  Foo & operator=(Foo &&) = delete;
  ```
  </td><td>

  ```cpp
  //! Deleted copy constructor
  Foo(const Foo &) = delete;
  //! Deleted move constructor
  Foo(Foo &&) = delete;
  //! Deleted copy assignment operator
  Foo & operator=(const Foo &) = delete;
  //! Deleted move assignment operator
  Foo & operator=(Foo &&) = delete;
  ```
  </td></tr></table></details>
- Do not use markdown headings in Doxygen

## Documenting features

Engine features are small 'building blocks' that the user (game developer) may
reference when building a game with the engine. Features do not necessarily map
1-1 to engine components or systems. If a component or system has a single,
distinct feature it should be named after that feature, not the component or
system itself.

The sources for these pages are located under `src/doc/feature/`, and have the
following format:

- A feature description which explains—
  - the purpose and function of the feature (focus on what it enables or
    achieves for the user)
  - additional information about when to implement the feature, such as specific
    use cases or scenarios
- A list of 'see also' references to relevant classes and/or types
- A **minimal** example to demonstrate how the feature is used. The example
  should be written such that the following is clear to the reader:
  - Which headers need to be included to utilize the feature
  - *Why* the example works, not what is happening in the example
  - Where is this code supposed to be called (e.g. inside scene/script
    functions)
  - Which restrictions should be kept in mind (e.g. copy/move semantics, max
    component instances, speed considerations)

Features should be documented as clear and concise as possible, so the following
points should be kept in mind:

- <details><summary>
  If a page expands on an example from another page, directly reference the
  other page using a cross-reference (`\ref`) in a `\note` block at the top of
  the page.
  </summary>

  ```
  \note This page builds on top of the example shown in \ref feature_script
  ```
  </details>
- When explaining the usage of specific functions, qualify them such that
  Doxygen is able to add a cross-reference or manually add a reference using the
  `\ref` command.
- Users will likely copy-paste examples as-is, so do this yourself to check if
  the example code actually works!

# Libraries

- External libraries should be included as Git submodules under the `lib/`
  subdirectory
- When adding new submodules, please set the `shallow` option to `true` in the
  [.gitmodules](./.gitmodules) file
- When adding new libraries, please update the library version table in
  [readme\.md](./readme.md)

[gtest-disable]: https://google.github.io/googletest/advanced.html#temporarily-disabling-tests

