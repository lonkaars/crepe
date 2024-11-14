#include <iostream>

#include <crepe/ComponentManager.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Metadata.h>
#include <crepe/api/Transform.h>

using namespace crepe;
using namespace std;

int main() {
	ComponentManager mgr{};

	// Create a few GameObjects
	try {
		GameObject body = mgr.new_object("body", "person", Vector2{0, 0}, 0, 1);
		GameObject right_leg
			= mgr.new_object("rightLeg", "person", Vector2{1, 1}, 0, 1);
		GameObject left_leg
			= mgr.new_object("leftLeg", "person", Vector2{1, 1}, 0, 1);
		GameObject right_foot
			= mgr.new_object("rightFoot", "person", Vector2{2, 2}, 0, 1);
		GameObject left_foot
			= mgr.new_object("leftFoot", "person", Vector2{2, 2}, 0, 1);

		// Set the parent of each GameObject
		right_foot.set_parent(right_leg);
		left_foot.set_parent(left_leg);
		right_leg.set_parent(body);
		left_leg.set_parent(body);

		// Adding a second Transform component is not allowed and will invoke an exception
		body.add_component<Transform>(Vector2{10, 10}, 0, 1);
	} catch (const exception & e) {
		cerr << e.what() << endl;
	}

	// Get the Metadata and Transform components of each GameObject
	vector<reference_wrapper<Metadata>> metadata
		= mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform
		= mgr.get_components_by_type<Transform>();

	// Print the Metadata and Transform components
	for (auto & m : metadata) {
		cout << "Id: " << m.get().game_object_id << " Name: " << m.get().name
			 << " Tag: " << m.get().tag << " Parent: " << m.get().parent
			 << " Children: ";
		for (auto & c : m.get().children) {
			cout << c << " ";
		}
		cout << endl;
	}
	for (auto & t : transform) {
		cout << "Id: " << t.get().game_object_id << " Position: ["
			 << t.get().position.x << ", " << t.get().position.y << "]" << endl;
	}

	return 0;
}
