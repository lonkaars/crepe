.PHONY: FORCE

FMT := $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
format: FORCE
	clang-tidy -p build/compile_commands.json --fix-errors $(FMT)

