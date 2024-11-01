# engine source

This folder contains the crêpe engine source files, unit tests, and some toy
examples. The only target built by default by the CMakeLists.txt in this folder
is the crêpe shared library object.

Examples (using Ninja):

```
$ cmake -B build -G Ninja
$ cmake --build build
```

Unit tests can be built by explicitly specifying the target `test_main` when
running the build command:

```
$ cmake --build build --target test_main
```

Each source file in the example/ folder corresponds to a CMake target as well
(all examples can be built at once by specifying the `examples` target):

```
$ cmake --build build --target audio_internal script
```

For installing crêpe system-wide after building (install must be run with
elevated privileges):

```
# cmake --install build
```

