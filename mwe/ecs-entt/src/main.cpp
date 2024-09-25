#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <entt/entt.hpp>

class Component {
public:
	Component() : mActive(true) {}
	virtual ~Component() {}

	bool mActive;
};

class Sprite : Component {
public:
	void render() {
		std::cout << "Rendering sprite" << std::endl;
	}
};

class Rigidboy : Component {
public:
	Rigidboy(int mass, int gravityScale, int bodyType) : mMass(mass), mGravityScale(gravityScale), mBodyType(bodyType) {}

	int mMass;
	int mGravityScale;
	int mBodyType;
};

class Systems {
public:
	Systems(entt::registry& registry) : mRegistry(registry) {}

	void spriteSystem() {
		auto view = mRegistry.view<Sprite>();
		for(entt::entity gameObject : view) {
			Sprite& sprite = view.get<Sprite>(gameObject);
			std::cout << "Current GameObject ID: " << (uint32_t)gameObject << std::endl;
			sprite.render();
			std::cout << std::endl;
		}
	}

	void rigidbodySystem() {
		auto view = mRegistry.view<Rigidboy>();
		for(entt::entity gameObject : view) {
			Rigidboy& rigidbody = view.get<Rigidboy>(gameObject);
			std::cout << "Current GameObject ID: " << (uint32_t)gameObject << std::endl;
			std::cout << rigidbody.mMass << " " << rigidbody.mGravityScale << " " << rigidbody.mBodyType << std::endl;
			std::cout << std::endl;
		}
	}

private:
	entt::registry& mRegistry;
};

class Scene {
public:
	Scene() : systems(mRegistry) {}

	void createScene() {
		addGameObject();
		addGameObject();

		addComponentToGameObject<Sprite>(mGameObjects[0]);
		addComponentToGameObject<Rigidboy>(mGameObjects[0], 10, 10, 5);
		addComponentToGameObject<Rigidboy>(mGameObjects[1], 20, 100, 25);
	}

	void runSystems() {
		systems.spriteSystem();
		systems.rigidbodySystem();
	}

private:
	void addGameObject() {
		mGameObjects.push_back(mRegistry.create());
	}

	template <typename T, typename... Args>
	void addComponentToGameObject(entt::entity gameObject, Args&&... args) {
    	mRegistry.emplace<T>(gameObject, std::forward<Args>(args)...);
	}

	std::vector<entt::entity> mGameObjects;
	entt::registry mRegistry;
	Systems systems;
};

int main() {
	Scene scene;

	scene.createScene();
	scene.runSystems();

	return 0;
}
