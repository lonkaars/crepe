.PHONY: FORCE

# STEPS FOR BIG CLEANUP
#
# 1. Change TODO to your name (in capitals) for each file in the list below
#    that is yours (or you are going to fix)
# 2. Update the name between parentheses below this list (see comment) to your
#    name
# 3. Create a git commit at this point (ensure `git status` reports "working
#    tree clean")
# 4. Run `make format` in the REPOSITORY ROOT DIRECTORY (NOT HERE), and start
#    fixing reported errors or miscorrections manually until everything works
#    again.
# 5. Once everything is working again, create another git commit, and create a
#    pull request. Make sure to ask someone to review the code standards for
#    each ENTIRE FILE in this pull request.

TODO += crepe/Collider.cpp
TODO += crepe/Collider.h
TODO += crepe/Particle.cpp
TODO += crepe/Particle.h
TODO += crepe/Position.h
TODO += crepe/api/AssetManager.cpp
TODO += crepe/api/AssetManager.h
TODO += crepe/api/AssetManager.hpp
TODO += crepe/api/CircleCollider.h
TODO += crepe/api/Color.cpp
TODO += crepe/api/Color.h
TODO += crepe/api/ParticleEmitter.cpp
TODO += crepe/api/ParticleEmitter.h
TODO += crepe/api/Vector2.h
TODO += crepe/api/Vector2.cpp
TODO += crepe/api/Sprite.cpp
TODO += crepe/api/Sprite.h
TODO += crepe/api/Texture.cpp
TODO += crepe/api/Texture.h
TODO += crepe/facade/SDLContext.cpp
TODO += crepe/facade/SDLContext.h
TODO += crepe/system/CollisionSystem.cpp
TODO += crepe/system/CollisionSystem.h
TODO += crepe/system/ParticleSystem.cpp
TODO += crepe/system/ParticleSystem.h
TODO += crepe/system/RenderSystem.cpp
TODO += crepe/system/RenderSystem.h
TODO += example/asset_manager.cpp
TODO += example/components_internal.cpp
TODO += example/particle.cpp
TODO += example/rendering.cpp

FMT := $(LOEK) #<<< CHANGE THIS TO YOUR NAME FOR STEP 2
format: FORCE
	clang-tidy -p build/compile_commands.json --fix-errors $(FMT)

# FMT += $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
# TODO: re-enable linter after all corrections

