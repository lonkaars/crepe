# crêpe

This repository contains:

|folder|content|
|-|-|
|`lib/`|third-party libraries as git submodules|
|`mwe/`|minimal working examples and proof-of-concepts|
|`src/crepe/`|game engine source code|
|`test/`|game engine unit tests|

## Compilation

This repository uses CMake (the makefile in the root of this repository is for
running auxiliary tasks only). Make sure you have initialized and updated the
submodules before compiling.

## Documentation

API documentation is done using Doxygen. To generate the docs, run `make
doxygen`.

## Code style

Please read [contributing.md](./contributing.md).

