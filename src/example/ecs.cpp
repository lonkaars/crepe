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
	GameObject leg(1, "leg", "person", Point{1, 1}, 0, 1);
	GameObject foot(2, "foot", "person", Point{2, 2}, 0, 1);

	foot.set_parent(leg);
	leg.set_parent(body);

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
