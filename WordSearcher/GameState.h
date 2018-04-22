#ifndef DREW_GAME_STATE_H
#define DREW_GAME_STATE_H

#include "Game.h"
#include "Definitions.h"
#include <vector>

namespace Drewski
{
	class GameState : public State
	{
	private:
		GameDataRef data;
		sf::Sprite background;
		//sf::Sprite pauseButton;
		//sf::Sprite gridSprite;
		//sf::Sprite gridPieces[GRID_HEIGHT * GRID_WIDTH];

		//int gridArray[GRID_HEIGHT * GRID_WIDTH];

		//int turn;
		//int gameState;

	public:
		GameState(GameDataRef dataIn);
		~GameState();

		void init();
		void handleInput();
		void update(float deltaTimeIn);
		void draw(float deltaTimeIn);
	};
}

#endif