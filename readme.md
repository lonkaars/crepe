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
submodules, which may be used if your distro's package manager does not provide
(recent enough versions of) them. To build any of the dependencies, make sure
the submodules are initialized by running:

```
$ git submodule update --init --recursive --depth 1
```

Then, follow these steps for each library you want to install:

1. Change into the library folder (run **one** of these):
   ```
   $ cd lib/googletest
   $ cd lib/sdl2
   $ cd lib/soloud/contrib
   $ cd lib/sdl_image
   ```
2. Use CMake to configure the build, run the build and install (run **all** of
   these):
   ```
   $ cmake -B build -G Ninja
   $ cmake --build build
   # cmake --install build
   ```

## Documentation

API documentation is done using Doxygen. To generate the docs, run
```
$ make doxygen
```

## Code style

Please read [contributing.md](./contributing.md).

