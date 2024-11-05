#include <iostream>

#include "../crepe/api/GameObject.h"
#include "../crepe/ComponentManager.h"
#include "../crepe/Metadata.h"
#include "../crepe/api/Transform.h"

using namespace crepe::api;
using namespace crepe;
using namespace std;

int main() {
	GameObject body(0, "body", "person", Point{0, 0}, 0, 1);
	GameObject rightLeg(1, "rightLeg", "person", Point{1, 1}, 0, 1);
	GameObject leftLeg(2, "leftLeg", "person", Point{1, 1}, 0, 1);
	GameObject rightFoot(3, "rightFoot", "person", Point{2, 2}, 0, 1);
	GameObject leftFoot(4, "leftFoot", "person", Point{2, 2}, 0, 1);

	rightFoot.set_parent(rightLeg);
	leftFoot.set_parent(leftLeg);
	rightLeg.set_parent(body);
	leftLeg.set_parent(body);

	ComponentManager & mgr = ComponentManager::get_instance();
	vector<reference_wrapper<Metadata>> metadata = mgr.get_components_by_type<Metadata>();
	vector<reference_wrapper<Transform>> transform = mgr.get_components_by_type<Transform>();

	for(auto & m : metadata) {
		cout << m.get().name << " " << m.get().tag << " " << m.get().parent << endl;
		for(auto & c : m.get().children) {
			cout << "    " << c << " " << endl;
		}
	}
	for(auto & t : transform) {
		cout << t.get().position.x << " " << t.get().position.y << endl;
	}

	return 0;
}
