#include <iostream>
#include <entt/entt.hpp>

class TestComponent {
public:
	TestComponent() {}
	TestComponent(int variable) {
		mVariable = variable;
	}

	void print() {
		std::cout << "TestComponent variable: " << mVariable << std::endl;
	}

private:
	int mVariable = 0;
};

int main() {
	entt::registry registry;	//The registry stores/manages all the entities and its components (it's a container) (just like the component manager described in the research document)

	entt::entity entity0 = registry.create();	//This creates an entity (be aware that an entity is nothing more than a std::uint32_t)
												//Be aware that "entity.somthing()" is not possible, because an entity is just a std::uint32_t
	entt::entity entity1 = registry.create();	//Add a second entity to the registry

	registry.emplace<TestComponent>(entity0);	//This adds the TestComponent component to entity0
	registry.emplace<TestComponent>(entity1, 1);	//TestComponent also has a non-default constructor. In the case of a constructor with arguments, you would just type "registry.emplace<TestComponent>(entity, argument1, argument2, etc.);"

	if(registry.all_of<TestComponent>(entity0)) {	//Returns true if TestComponent is (one of) the component(s) of the entity
		TestComponent& testComponent = registry.get<TestComponent>(entity0);	//Gets the reference to the TestComponent component of this entity
    	testComponent.print();	//Do something with the component
	} else {
    	std::cout << "Entity does not have a TestComponent!" << std::endl;
	}

	auto view = registry.view<TestComponent>();	//This returns all entities that have the TestComponent component
	for(entt::entity entity : view) {	//Loop through all entities that have the TestComponent component
		TestComponent& testComponent = view.get<TestComponent>(entity);	//Get the reference to the TestComponent component of this entity
		testComponent.print();	//Do something with the component
	}

	return 0;
}
