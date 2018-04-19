#include <iostream>

#include "Definitions.h"
#include "Game.h"

using namespace std;

int main(int argc, char **argv)
{
	Drewski::Game game(SCREEN_WIDTH, SCREEN_HEIGHT, DEFAULT_GAME_TITLE);

	return EXIT_SUCCESS;
}