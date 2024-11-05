#include <iostream>

#include "../crepe/ComponentManager.h"
#include "../crepe/Metadata.h"
#include "../crepe/api/GameObject.h"
#include "../crepe/api/Transform.h"

using namespace crepe::api;
using namespace crepe;
using namespace std;

int main() {
	// Create a few GameObjects
	try {
		GameObject body(0, "body", "person", Point{0, 0}, 0, 1);
		GameObject rightLeg(1, "rightLeg", "person", Point{1, 1}, 0, 1);
		GameObject leftLeg(2, "leftLeg", "person", Point{1, 1}, 0, 1);
		GameObject rightFoot(3, "rightFoot", "person", Point{2, 2}, 0, 1);
		GameObject leftFoot(4, "leftFoot", "person", Point{2, 2}, 0, 1);

		// Set the parent of each GameObject
		rightFoot.set_parent(rightLeg);
		leftFoot.set_parent(leftLeg);
		rightLeg.set_parent(body);
		leftLeg.set_parent(body);

		// Get the Metadata and Transform components of each GameObject
		ComponentManager & mgr = ComponentManager::get_instance();
		vector<reference_wrapper<Metadata>> metadata
			= mgr.get_components_by_type<Metadata>();
		vector<reference_wrapper<Transform>> transform
			= mgr.get_components_by_type<Transform>();

		// Print the Metadata and Transform components
		for (auto & m : metadata) {
			cout << "Id: " << m.get().game_object_id
				 << " Name: " << m.get().name << " Tag: " << m.get().tag
				 << " Parent: " << m.get().parent << " Children: ";
			for (auto & c : m.get().children) {
				cout << c << " ";
			}
			cout << endl;
		}
		for (auto & t : transform) {
			cout << "Id: " << t.get().game_object_id << " Position: ["
				 << t.get().position.x << ", " << t.get().position.y << "]"
				 << endl;
		}
	} catch (const exception & e) {
		cerr << e.what() << endl;
	}

	return 0;
}
