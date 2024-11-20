.PHONY: FORCE

doxygen: Doxyfile FORCE
	doxygen

FMT += $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
format: FORCE
	clang-format -i $(FMT)
	#$(MAKE) -C src $@

