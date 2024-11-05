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

- ASCII only

  ```cpp
  // Good
  std::string message = "Hello, world!";
  
  // Bad
  std::string message = "こんにちは世界";
  ```

- Class names are always singular

  ```cpp
  // Good
  class Car {};
  
  // Bad
  class Cars {};
  ```

- Explanatory comments are placed above the line(s) they are explaining

  ```cpp
  // Good
  // This function adds two numbers
  int add(int a, int b) {
      return a + b;
  }
  
  // Bad
  int add(int a, int b) {
      return a + b; // This function adds two numbers
  }
  ```

- Source files should only contain comments that plainly state what the code is supposed to do

  ```cpp
  // Good
  // Initialize the engine
  engine.init();
  
  // Bad
  // Initialize the engine with default settings and prepare it for running
  engine.init();
  ```

- Explanatory comments in headers may be used to clarify implementation design decisions

  ```cpp
  // Good
  // This class handles the rendering process
  class Renderer {
      // This method initializes the rendering context
      void init_context();
  };
  
  // Bad
  class Renderer {
      void init_context(); // This method initializes the rendering context
  };
  ```

- Formatting nitty-gritty is handled by clang-format/clang-tidy (run `make format` in the root folder of this repository to format all sources files)


- Header includes are split into paragraphs separated by a blank line. The order is:
  1. system headers (using `<`brackets`>`)
  2. relative headers NOT in the same folder as the current file
  3. relative headers in the same folder as the current file

  ```cpp
  // Good
  #include <iostream>
  
  #include "utils/helper.h"
  
  #include "main.h"
  
  // Bad
  #include "main.h"
  #include <iostream>
  #include "utils/helper.h"
  ```

- When using libraries of which the header include order is important, make sure to separate the include statements using a blank line (clang-format may sort include statements, but does not sort across empty lines).

  ```cpp
  // Good
  #include <iostream>
  
  #include <boost/algorithm/string.hpp>
  
  // Bad
  #include <iostream>
  #include <boost/algorithm/string.hpp>
  ```

- All engine-related code is implemented under the `crepe` namespace, user-facing APIs under `crepe::api` (the folder structure should also reflect this).


- `using namespace` may not be used in header files, only in source files.

  ```cpp
  // Good
  // header.h
  namespace crepe {
      void init();
  }
  
  // source.cpp
  #include "header.h"
  using namespace crepe;
  void init() {}
  
  // Bad
  // header.h
  using namespace crepe;
  void init();
  ```

- Do not (indirectly) include private *dependency* headers in API header files, as these are no longer accessible when the engine is installed

  ```cpp
  // Good
  // api.h
  namespace crepe::api {
      void start();
  }
  
  // Bad
  // api.h
  #include "private_dependency.h"
  namespace crepe::api {
      void start();
  }
  ```

- Getter and setter functions are appropriately prefixed with `get_` and `set_`.

  ```cpp
  // Good
  class Car {
  public:
      int get_speed() const;
      void set_speed(int speed);
  private:
      int speed;
  };
  
  // Bad
  class Car {
  public:
      int speed() const;
      void speed(int speed);
  private:
      int speed;
  };
  ```

- Doxygen commands are used with a backslash instead of an at-sign (i.e. `\brief` instead of `@brief`)

  ```cpp
  // Good
  /// \brief This function adds two numbers
  int add(int a, int b);
  
  // Bad
  /// @brief This function adds two numbers
  int add(int a, int b);
  ```

- A singleton's instance is always accessed using a getter function that instantiates its own class as a static variable within the getter function scope, instead of storing the instance as a member variable directly:

  ```cpp
  class Bad {
      static Bad instance;
      Bad & get_instance() { return instance; }
  };

  class Good {
      Good & get_instance() {
          static Good instance;
          return instance;
      }
  };
  ```

- Member variable default values should be directly defined in the class declaration instead of using the constructor.

  ```cpp
  // Good
  class Car {
  private:
      int speed = 0;
  };
  
  // Bad
  class Car {
  private:
      int speed;
      Car() : speed(0) {}
  };
  ```

- Header files declare either a single class or symbols within a single namespace.

  ```cpp
  // Good
  // car.h
  namespace crepe {
      class Car {};
  }
  
  // Bad
  // car.h
  namespace crepe {
      class Car {};
      class Engine {};
  }
  ```

- Use of the `auto` type is not allowed, with the following exceptions:
  - When naming the item type in a range-based for loop
  - When calling template factory methods that explicitly name the return type in the function call signature
  - When fetching a singleton instance

  ```cpp
  // Good
  for (auto item : items) {}
  
  auto instance = Singleton::get_instance();
  
  // Bad
  auto speed = car.get_speed();
  ```

- Only use member initializer lists for non-trivial types.

  ```cpp
  // Good
  class Car {
  public:
      Car() : engine("V8") {}
  private:
      std::string engine;
  };
  
  // Bad
  class Car {
  public:
      Car() : speed(0) {}
  private:
      int speed;
  };
  ```

- C++-style structs should define default values for all non-trivial fields.

  ```cpp
  // Good
  struct Car {
      std::string model = "Unknown";
  };
  
  // Bad
  struct Car {
      std::string model;
      Car() : model("Unknown") {}
  };
  ```

- Declare incomplete classes instead of including the relevant header where possible (i.e. if you only need a reference or pointer type).

  ```cpp
  // Good
  class Engine;
  class Car {
      Engine* engine;
  };
  
  // Bad
  #include "engine.h"
  class Car {
      Engine* engine;
  };
  ```

- Template functions are only declared in a `.h` header, and defined in a matching `.hpp` header.

  ```cpp
  // Good
  // add.h
  template <typename T>
  T add(T a, T b);
  
  // add.hpp
  #include "add.h"
  template <typename T>
  T add(T a, T b) {
      return a + b;
  }
  
  // Bad
  // add.h
  template <typename T>
  T add(T a, T b) {
      return a + b;
  }
  ```

- Where possible, end (initializer) lists with a trailing comma (e.g. with structs, enums)

  ```cpp
  // Good
  enum Color {
      Red,
      Green,
      Blue,
  };
  
  // Bad
  enum Color {
      Red,
      Green,
      Blue
  };
  ```

## CMakeLists specific

- Make sure list arguments (e.g. sources, libraries) given to commands (e.g.
  `target_sources`, `target_link_libraries`) are on separate lines. This makes
  resolving merge conflicts when multiple sources were added by different
  people to the same CMakeLists.txt easier.

# Documentation

- All documentation is written in U.S. English

# Libraries

- External libraries should be included as Git submodules under the `lib/`
  subdirectory
- When adding new submodules, please set the `shallow` option to `true` in the
  [.gitmodules](./.gitmodules) file

