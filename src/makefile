.PHONY: FORCE

FMT += $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
format: FORCE
	# clang-tidy -p build/compile_commands.json --fix-errors $(FMT)

# TODO: re-enable linter after 2024-11-10

