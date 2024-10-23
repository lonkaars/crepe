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
- Class names are always singular
- Explanatory comments are placed above the line(s) they are explaining
- Source files should only contain comments that plainly state what the code is
  supposed to do
- Explanatory comments in headers may be used to clarify implementation design
  decisions
- Formatting nitty-gritty is handled by clang-format/clang-tidy (run `make
  format` in the root folder of this repository to format all sources files)
- Header includes are split into paragraphs separated by a blank line. The
  order is:
  1. system headers (using `<`brackets`>`)
  2. relative headers NOT in the same folder as the current file
  3. relative headers in the same folder as the current file
- When using libraries of which the header include order is important, make
  sure to separate the include statements using a blank line (clang-format may
  sort include statements, but does not sort across empty lines).
- All engine-related code is implemented under the `crepe` namespace,
  user-facing APIs under `crepe::api` (the folder structure should also reflect
  this).
- `using namespace` may not be used in header files, only in source files.
- Do not (indirectly) include private *dependency* headers in API header files,
  as these are no longer accessible when the engine is installed
- Getter and setter functions are appropriately prefixed with `get_` and
  `set_`.
- Doxygen commands are used with a backslash instead of an at-sign (i.e.
  `\brief` instead of `@brief`)
- A singleton's instance is always accessed using a getter function that
  instantiates its own class as a static variable within the getter function
  scope, instead of storing the instance as a member variable directly:

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
- Member variable default values should be directly defined in the class
  declaration instead of using the constructor.
- Header files declare either a single class or symbols within a single
  namespace.
- Only use member initializer lists for non-trivial types.
- C++-style structs should define default values for all non-trivial fields.
- Declare incomplete classes instead of including the relevant header where
  possible (i.e. if you only need a reference or pointer type).
- Template functions are only declared in a `.h` header, and defined in a
  matching `.hpp` header.

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

