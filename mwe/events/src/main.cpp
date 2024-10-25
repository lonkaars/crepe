#include "event.h"
#include "loopManager.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
<<<<<<< HEAD
#include "loopManager.h"
#include "event.h"
#include "customTypes.h"
=======

>>>>>>> b3b762a34e7ccb4a0dcd041a693ac7180af16002
class PlayerDamagedEvent : public Event {
public:
	PlayerDamagedEvent(int damage, int playerID)
		: Event("PlayerDamaged"), damage(damage), playerID(playerID) {}

	REGISTER_EVENT_TYPE(PlayerDamagedEvent);

<<<<<<< HEAD
    int getDamage() const { return damage; }
    int getPlayerID() const { return playerID; }
	
=======
	int getDamage() const { return damage; }
	int getPlayerID() const { return playerID; }

>>>>>>> b3b762a34e7ccb4a0dcd041a693ac7180af16002
private:
	int damage;
	int playerID;
};
void onPlayerDamaged(const PlayerDamagedEvent & e) {
	std::cout << "Player " << e.getPlayerID() << " took " << e.getDamage()
			  << " damage." << std::endl;
}

<<<<<<< HEAD
void onKeyPressed1(const KeyPressedEvent& e)
{
   int keyCode = e.getKeyCode();
	fprintf(stderr,"first function KeyCode %d\n",keyCode);
}
void onKeyPressed(const KeyPressedEvent& e)
{
   int keyCode = e.getKeyCode();
	fprintf(stderr,"second function KeyCode %d\n",keyCode);
}
void CollisionHandler(const CollisionEvent& e){
	std::cout << "collision betwee object id: "<< e.getCollisionData().objectIdA << " and id: " << e.getCollisionData().objectIdB << std::endl;
}
void testCollisionEvent() {
	Collision testCollision(1, 2, {3, 4}, {5, 6}, 7.8f);
	subscribe<CollisionEvent>(CollisionHandler,1);
	// EventHandler<PlayerDamagedEvent>
	triggerEvent(CollisionEvent(testCollision), 1);
=======
void onKeyPressed(const KeyPressedEvent & e) {
	const int keyCode = e.getKeyCode();
	fprintf(stderr, "KeyCode %d\n", keyCode);
>>>>>>> b3b762a34e7ccb4a0dcd041a693ac7180af16002
}
int main(int argc, char * args[]) {
	LoopManager gameLoop;
	// Create an event handler for KeyPressedEvent
	// EventHandler<KeyPressedEvent> callback = [](const KeyPressedEvent& e) {
	//     onKeyPressed(e);
	// };
	// custom event class poc
	subscribe<PlayerDamagedEvent>(onPlayerDamaged);
	triggerEvent(PlayerDamagedEvent(50, 1));
<<<<<<< HEAD
    subscribe<KeyPressedEvent>(onKeyPressed,1,false);
    subscribe<KeyPressedEvent>(onKeyPressed1,false);
    // queueEvent(std::move(anotherKeyPressEvent));
    triggerEvent(KeyPressedEvent(42), 1);
	
=======
	//EventHandler<KeyPressedEvent> callback = onKeyPressed;
	//subscribe<KeyPressedEvent>(callback,false);
	std::unique_ptr<Event> anotherKeyPressEvent
		= std::make_unique<KeyPressedEvent>(65);
	queueEvent(std::move(anotherKeyPressEvent));
	triggerEvent(KeyPressedEvent(42));
>>>>>>> b3b762a34e7ccb4a0dcd041a693ac7180af16002
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
