#include "Game.h"
#include "MenuGUI.h"

int main() {

	//Initialize random seed
	srand(static_cast<unsigned>(time(NULL)));

	//Initialize game object 
	MenuGUI menu;

	//Game loop
	menu.runMenu();
	
	return 0;
}