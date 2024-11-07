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
TODO += crepe/Component.cpp
TODO += crepe/Component.h
TODO += crepe/ComponentManager.cpp
TODO += crepe/ComponentManager.h
TODO += crepe/ComponentManager.hpp
TODO += crepe/Metadata.cpp
TODO += crepe/Metadata.h
TODO += crepe/Particle.cpp
TODO += crepe/Particle.h
TODO += crepe/Position.h
NIELS += crepe/api/AssetManager.cpp
NIELS += crepe/api/AssetManager.h
NIELS += crepe/api/AssetManager.hpp
LOEK += crepe/api/AudioSource.cpp
LOEK += crepe/api/AudioSource.h
LOEK += crepe/api/BehaviorScript.cpp
LOEK += crepe/api/BehaviorScript.h
LOEK += crepe/api/BehaviorScript.hpp
TODO += crepe/api/CircleCollider.h
NIELS += crepe/api/Color.cpp
NIELS += crepe/api/Color.h
LOEK += crepe/api/Config.h
TODO += crepe/api/Force.cpp
TODO += crepe/api/Force.h
TODO += crepe/api/GameObject.cpp
TODO += crepe/api/GameObject.h
TODO += crepe/api/GameObject.hpp
TODO += crepe/api/ParticleEmitter.cpp
TODO += crepe/api/ParticleEmitter.h
TODO += crepe/api/Point.h
TODO += crepe/api/Rigidbody.cpp
TODO += crepe/api/Rigidbody.h
LOEK += crepe/api/Script.cpp
LOEK += crepe/api/Script.h
LOEK += crepe/api/Script.hpp
NIELS += crepe/api/Sprite.cpp
NIELS += crepe/api/Sprite.h
NIELS += crepe/api/Texture.cpp
NIELS += crepe/api/Texture.h
NIELS += crepe/api/Transform.cpp
NIELS += crepe/api/Transform.h
TODO += crepe/facade/SDLApp.cpp
TODO += crepe/facade/SDLApp.h
NIELS += crepe/facade/SDLContext.cpp
NIELS += crepe/facade/SDLContext.h
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
NIELS += crepe/system/RenderSystem.cpp
NIELS += crepe/system/RenderSystem.h
LOEK += crepe/system/ScriptSystem.cpp
LOEK += crepe/system/ScriptSystem.h
LOEK += crepe/system/System.h
LOEK += crepe/util/LogColor.cpp
LOEK += crepe/util/LogColor.h
LOEK += crepe/util/fmt.cpp
LOEK += crepe/util/fmt.h
LOEK += crepe/util/log.cpp
LOEK += crepe/util/log.h
NIELS += example/asset_manager.cpp
LOEK += example/audio_internal.cpp
TODO += example/components_internal.cpp
TODO += example/ecs.cpp
LOEK += example/log.cpp
TODO += example/particle.cpp
TODO += example/physics.cpp
NIELS += example/rendering.cpp
NIELS += example/animator.cpp
LOEK += example/script.cpp
LOEK += test/audio.cpp
LOEK += test/dummy.cpp

FMT := $(NIELS) #<<< CHANGE THIS TO YOUR NAME FOR STEP 2
format: FORCE
	clang-tidy -p build/compile_commands.json --fix-errors $(FMT)

# FMT += $(shell git ls-files '*.c' '*.cpp' '*.h' '*.hpp')
# TODO: re-enable linter after all corrections

