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
- TODO: tagging / versions

# Code style

- Formatting nitty-gritty is handled by clang-format/clang-tidy (run `make
  format` in the root folder of this repository to format all sources files)
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
- Source files (<code>.cpp</code>, <code>.hpp</code>) contain the following types of comments:
  - What is the code supposed to do (optional)
  - Implementation details (if applicable)
- Header files (.h) contain the following types of comments:
  - Usage documentation (required)

    > [!NOTE]
    > Constructors/destructors aren't required to have a `\brief` description
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
- Header includes are split into paragraphs separated by a blank line. The
  order is:
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
  <code>using namespace</code> may not be used in header files (.h, .hpp), only
  in source files (.cpp).
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  example.h:
  ```cpp
  namespace crepe {
  void foo();
  }
  ```
  
  example.cpp:
  ```cpp
  #include "example.h"
  using namespace crepe;
  void foo() {}
  ```
  </td><td>

  example.h:
  ```cpp
  namespace crepe {
  template <typename T>
  T foo();
  }
  ```
  
  example.hpp:
  ```cpp
  #include "example.h"
  using namespace crepe;
  template <typename T>
  T foo();
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
  Variables that are being moved always use the fully qualified <code>std::move</code>
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
  Follow the rule-of-five
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  class Foo {
  public:
    Foo();
    ~Foo();
    Foo(const Foo &);
    Foo(Foo &&) noexcept;
    Foo & operator=(const Foo &);
    Foo & operator=(Foo &&) noexcept;
  };
  ```
  </td><td>

  ```cpp
  class Foo {
  public:
    Foo();
    ~Foo();
    Foo(const Foo &);
  };
  ```
  </td></tr></table></details>
- <details><summary>
  Ensure const-correctness
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
  File names (<code>.h</code>, <code>.cpp</code>, <code>.hpp</code>) should be written using CamelCase
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
  Implementation is not allowed in header files, except if the method only returns a constant value
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
  Use angle brackets (<code><></code>) for including libraries and double quotes (<code>""</code>) for including local files.
  </summary><table><tr><th>Good</th><th>Bad</th></tr><tr><td>

  ```cpp
  #include <iostream>
  #include "MyClass.h"
  ```
  </td><td>

  ```cpp
  #include "iostream"
  #include <MyClass.h>
  ```
  </td></tr></table></details>

## CMakeLists-specific

- Make sure list arguments (e.g. sources, libraries) given to commands (e.g.
  `target_sources`, `target_link_libraries`) are on separate lines. This makes
  resolving merge conflicts when multiple sources were added by different
  people to the same CMakeLists.txt easier.

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

# Libraries

- External libraries should be included as Git submodules under the `lib/`
  subdirectory
- When adding new submodules, please set the `shallow` option to `true` in the
  [.gitmodules](./.gitmodules) file

