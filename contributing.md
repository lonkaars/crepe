# Contributing new code

- Please do the following *before* sending a pull request:
  - Merge upstream code (if any) back into your own branch
  - Run formatters/linters

# Git

- TODO: tagging / versions
- TODO: branch stability / gitflow?

# Code style

- Formatting nitty-gritty is handled by clang-format/clang-tidy
- ASCII only
- When using libraries of which the header include order is important, make
  sure to separate the include statements using a blank line (clang-format may
  sort include statements, but does not sort across empty lines).

# Documentation

- All documentation is written in U.S. English
- TODO

# Libraries

- External libraries should be included as Git submodules under the `lib/`
  subdirectory

