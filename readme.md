# crêpe

This repository contains:

|folder|content|
|-|-|
|`lib/`|third-party libraries as git submodules|
|`mwe/`|minimal working examples and standalone proof-of-concepts (isolated from the engine)|
|`src/crepe/`|game engine source code|
|`src/test/`|unit tests|
|`src/example/`|standalone examples or proof-of-concepts using game engine internals|

## Compilation

This repository uses CMake (the makefile in the root of this repository is for
running auxiliary tasks only). See [src/readme.md](src/readme.md) for detailed
building instructions.

## Code style

Please read [contributing.md](./contributing.md).

## Libraries

This project uses the following libraries

|Name|Version|
|-|-:|
|`SDL2`|2.30.9|
|`SDL2_image`|2.8.2|
|`SDL_ttf`|2.22.0|
|`SoLoud`|(latest git `master` version)|
|Google Test (`GTest`)|1.15.2|
|Berkeley DB (`libdb`)|5.3.21|
|Where Am I?|(latest git `master` version)

> [!NOTE]
> Most of these libraries are likely available from your package manager if you
> are using Linux or MinGW. Make sure your entire distribution is up-to-date if
> you are not using a rolling release distribution.

The sources for all of the above libraries are also included in this repository
as git submodules, which may be used if your distro's package manager does not
provide (recent enough versions of) them. To build any of the libraries
manually, make sure the submodules are initialized by running:

```
$ git submodule update --init --recursive --depth 1
```

Then, follow these steps for each library you want to install:

> [!IMPORTANT]
> A dollar sign prompt (`$`) indicates commands to be run as a regular user,
> while a hashtag (`#`) is used to denote commands that must be run with
> privileges (e.g. as root or using `sudo`).

1. Change into the library folder (run **one** of these):
   ```
   $ cd lib/googletest
   $ cd lib/sdl2
   $ cd lib/soloud/contrib
   $ cd lib/sdl_ttf
   $ cd lib/sdl_image
   $ cd lib/sdl_ttf
   $ cd lib/whereami
   ```
2. Use CMake to configure the build, run the build and install (run **all** of
   these):
   ```
   $ cmake -B build -G Ninja
   $ cmake --build build
   # cmake --install build
   ```

## Tooling

- TODO

## Documentation

API documentation is done using Doxygen. To generate the docs, run
```
$ make doxygen
```

