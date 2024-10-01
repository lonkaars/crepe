#include <SDL2/SDL.h>
#include <stdio.h>
#include "event.h"


int main(int argc, char * args[]) {
	
	KeyPressedEvent keyEvent(1,1);
	KeyReleasedEvent keyRelease(1);
	std::cout << keyEvent.GetEventType() << std::endl;
	std::cout << keyRelease.GetEventType() << std::endl;
	std::cin;
	return 0;
}
