all: $(TARGET) # TARGET is defined in lazy.mk (build/main)

.PHONY: FORCE

doxygen: Doxyfile FORCE
	doxygen

FMT += $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
format: FORCE
	clang-format -i $(FMT)
# clang tidy doesn't work that well :/
# clang-tidy --fix-errors $(FMT)

