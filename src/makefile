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

LOEK += crepe/Asset.cpp
LOEK += crepe/Asset.h
TODO += crepe/Collider.cpp
TODO += crepe/Collider.h
MAX += crepe/Component.cpp
MAX += crepe/Component.h
MAX += crepe/ComponentManager.cpp
MAX += crepe/ComponentManager.h
MAX += crepe/ComponentManager.hpp
MAX += crepe/Metadata.cpp
MAX += crepe/Metadata.h
TODO += crepe/Particle.cpp
TODO += crepe/Particle.h
TODO += crepe/Position.h
TODO += crepe/api/AssetManager.cpp
TODO += crepe/api/AssetManager.h
TODO += crepe/api/AssetManager.hpp
LOEK += crepe/api/AudioSource.cpp
LOEK += crepe/api/AudioSource.h
LOEK += crepe/api/BehaviorScript.cpp
LOEK += crepe/api/BehaviorScript.h
LOEK += crepe/api/BehaviorScript.hpp
TODO += crepe/api/CircleCollider.h
TODO += crepe/api/Color.cpp
TODO += crepe/api/Color.h
LOEK += crepe/api/Config.h
TODO += crepe/api/Force.cpp
TODO += crepe/api/Force.h
MAX += crepe/api/GameObject.cpp
MAX += crepe/api/GameObject.h
MAX += crepe/api/GameObject.hpp
TODO += crepe/api/ParticleEmitter.cpp
TODO += crepe/api/ParticleEmitter.h
TODO += crepe/api/Point.h
TODO += crepe/api/Rigidbody.cpp
TODO += crepe/api/Rigidbody.h
LOEK += crepe/api/Script.cpp
LOEK += crepe/api/Script.h
LOEK += crepe/api/Script.hpp
TODO += crepe/api/Sprite.cpp
TODO += crepe/api/Sprite.h
TODO += crepe/api/Texture.cpp
TODO += crepe/api/Texture.h
MAX += crepe/api/Transform.cpp
MAX += crepe/api/Transform.h
TODO += crepe/facade/SDLApp.cpp
TODO += crepe/facade/SDLApp.h
TODO += crepe/facade/SDLContext.cpp
TODO += crepe/facade/SDLContext.h
LOEK += crepe/facade/Sound.cpp
LOEK += crepe/facade/Sound.h
LOEK += crepe/facade/SoundContext.cpp
LOEK += crepe/facade/SoundContext.h
TODO += crepe/system/CollisionSystem.cpp
TODO += crepe/system/CollisionSystem.h
TODO += crepe/system/ParticleSystem.cpp
TODO += crepe/system/ParticleSystem.h
TODO += crepe/system/PhysicsSystem.cpp
TODO += crepe/system/PhysicsSystem.h
TODO += crepe/system/RenderSystem.cpp
TODO += crepe/system/RenderSystem.h
LOEK += crepe/system/ScriptSystem.cpp
LOEK += crepe/system/ScriptSystem.h
LOEK += crepe/system/System.h
LOEK += crepe/util/LogColor.cpp
LOEK += crepe/util/LogColor.h
LOEK += crepe/util/fmt.cpp
LOEK += crepe/util/fmt.h
LOEK += crepe/util/log.cpp
LOEK += crepe/util/log.h
TODO += example/asset_manager.cpp
LOEK += example/audio_internal.cpp
TODO += example/components_internal.cpp
MAX += example/ecs.cpp
LOEK += example/log.cpp
TODO += example/particle.cpp
TODO += example/physics.cpp
TODO += example/rendering.cpp
LOEK += example/script.cpp
LOEK += test/audio.cpp
LOEK += test/dummy.cpp

FMT := $(MAX) #<<< CHANGE THIS TO YOUR NAME FOR STEP 2
format: FORCE
	clang-tidy -p build/compile_commands.json --fix-errors $(FMT)

# FMT += $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
# TODO: re-enable linter after all corrections

