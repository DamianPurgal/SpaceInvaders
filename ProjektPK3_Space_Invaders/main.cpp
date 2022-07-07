#include <SFML/Graphics.hpp>
#include "Game.h"

//---------------------------------------------------------------------

int main()
{

	Game* a = new Game();
	a->startGame();
	delete a;

	return 0;
}

//---------------------------------------------------------------------