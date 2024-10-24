#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "loopManager.h"
#include "event.h"

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
void onPlayerDamaged(const PlayerDamagedEvent& e) {
    std::cout << "Player " << e.getPlayerID() << " took " << e.getDamage() << " damage." << std::endl;
}

void onKeyPressed(const KeyPressedEvent& e)
{
   const int keyCode = e.getKeyCode();
	fprintf(stderr,"KeyCode %d\n",keyCode);
}
int main(int argc, char* args[]) {
	LoopManager gameLoop;
	// Create an event handler for KeyPressedEvent
    // EventHandler<KeyPressedEvent> callback = [](const KeyPressedEvent& e) {
    //     onKeyPressed(e);
    // };
	// custom event class poc
	EventHandler<PlayerDamagedEvent> playerDamagedHandler = onPlayerDamaged;
	subscribe<PlayerDamagedEvent>(playerDamagedHandler);

	triggerEvent(PlayerDamagedEvent(50, 1));
	//EventHandler<KeyPressedEvent> callback = onKeyPressed;
    //subscribe<KeyPressedEvent>(callback,false);
	std::unique_ptr<Event> anotherKeyPressEvent = std::make_unique<KeyPressedEvent>(65);
    queueEvent(std::move(anotherKeyPressEvent));
    triggerEvent(KeyPressedEvent(42));
	EventManager::getInstance().dispatchEvents();
	gameLoop.setup();
	gameLoop.loop();
    return 0;
}
