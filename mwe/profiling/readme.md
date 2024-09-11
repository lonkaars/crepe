# profiling test

Test how callgrind handles executables that call library functions from
libraries w/o debug symbols.

To collect run info, run

```
$ valgrind --tool=callgrind build/main
```

