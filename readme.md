# crêpe

This repository contains:

|folder|content|
|-|-|
|`lib/`|third-party libraries as git submodules|
|`mwe/`|minimal working examples and proof-of-concepts|
|`src/crepe/`|game engine source code|
|`src/test/`|unit tests|
|`src/example/`|standalone examples using game engine|

## Compilation

This repository uses CMake (the makefile in the root of this repository is for
running auxiliary tasks only). See [src/readme.md](src/readme.md) for detailed
building instructions.

## Installing libraries

The expected library (source) versions are included in this repository as git
submodules. Follow these steps for manually building one of the required
libraries from source:

1. Ensure the git submodules are initialized:
   ```
   $ git submodule update --init --recursive --depth 1
   ```
2. `cd` into the library source folder:
   ```
   $ cd lib/googletest
   or
   $ cd lib/sdl2
   or
   $ cd lib/soloud/contrib
   ```
3. Configure the build, run the build and install:
   ```
   $ cmake -B build -G Ninja
   $ ninja -C build
   # ninja -C build install
   ```

## Documentation

API documentation is done using Doxygen. To generate the docs, run
```
$ make doxygen
```

## Code style

Please read [contributing.md](./contributing.md).

