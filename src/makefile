.PHONY: FORCE

format: FORCE
	$(MAKE) -C .. $@

LINT := $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
lint: FORCE
	clang-tidy -p build/compile_commands.json --fix-errors $(LINT)

