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
- Formatting nitty-gritty is handled by clang-format/clang-tidy (run `make
  format` in the root folder of this repository to format all sources files)
- When using libraries of which the header include order is important, make
  sure to separate the include statements using a blank line (clang-format may
  sort include statements, but does not sort across empty lines).
- All engine-related code is implemented under the `crepe` namespace,
  user-facing APIs under `crepe::api` (the folder structure should also reflect
  this).
- `using namespace` may not be used in header files, only in source files.
- Do not (indirectly) include private dependency headers in API header files,
  as these are no longer accessible when the engine is installed
- Getter and setter functions are appropriately prefixed with `get_` and
  `set_`.

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

