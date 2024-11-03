#include "customTypes.h"
#include "event.h"
#include "loopManager.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "loopManager.h"
#include "event.h"
#include "customTypes.h"
#include "iKeyListener.h"
#include "iMouseListener.h"
#include "keyListenerTest.h"
#include "mouseListenerTest.h"
class PlayerDamagedEvent : public Event {
public:
	PlayerDamagedEvent(int damage, int playerID)
		: Event("PlayerDamaged"), damage(damage), playerID(playerID) {}

	REGISTER_EVENT_TYPE(PlayerDamagedEvent);

	int getDamage() const { return damage; }
	int getPlayerID() const { return playerID; }

private:
	int damage;
	int playerID;
};
void onPlayerDamaged(const PlayerDamagedEvent & e) {
	std::cout << "Player " << e.getPlayerID() << " took " << e.getDamage()
			  << " damage." << std::endl;
}

void onKeyPressed1(const KeyPressedEvent & e) {
	int keyCode = e.getKeyCode();
	fprintf(stderr, "first function KeyCode %d\n", keyCode);
}
void onKeyPressed(const KeyPressedEvent & e) {
	int keyCode = e.getKeyCode();
	fprintf(stderr, "second function KeyCode %d\n", keyCode);
}
void CollisionHandler(const CollisionEvent & e) {
	std::cout << "collision betwee object id: "
			  << e.getCollisionData().objectIdA
			  << " and id: " << e.getCollisionData().objectIdB << std::endl;
}
void testCollisionEvent() {
	Collision testCollision(1, 2, {3, 4}, {5, 6}, 7.8f);
	subscribe<CollisionEvent>(CollisionHandler, 1);
	// EventHandler<PlayerDamagedEvent>
	triggerEvent(CollisionEvent(testCollision), 1);
}
int main(int argc, char * args[]) {
	LoopManager gameLoop;
	int testListenerId = 0;
	KeyListenerTest keyListener(testListenerId);
    MouseListenerTest mouseListener(testListenerId);
	// custom event class poc
	subscribe<PlayerDamagedEvent>(onPlayerDamaged);
	triggerEvent(PlayerDamagedEvent(50, 1));
	subscribe<KeyPressedEvent>(onKeyPressed, 1, false);
	subscribe<KeyPressedEvent>(onKeyPressed1, false);
	// queueEvent(std::move(anotherKeyPressEvent));
	triggerEvent(KeyPressedEvent(42), 1);

	EventManager::getInstance().dispatchEvents();
	//collision event call
	testCollisionEvent();

	gameLoop.setup();
	gameLoop.loop();
	return 0;
}
// void collisionUpdate(){
// 	int count;
// 	//iedere collision
// 	for (int i = 0; i < count; i++)
// 	{
// 		//trigger object 1
// 		//triger object 2
// 		triggerEvent(CollisionEvent(1,2),1);
// 		triggerEvent(CollisionEvent(1,2),2);
// 	}

// }
// int main(){

// 	return 0;
// }
