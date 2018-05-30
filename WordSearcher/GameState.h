// Created by: Andrew Steven Michel
// Date Created: May 2018
#ifndef DREW_GAME_STATE_H
#define DREW_GAME_STATE_H

// IMPORTED PACKAGES:
#include "Game.h"
#include "Definitions.h"
#include <vector>

// Namespace declaration
namespace Drewski
{
	// Class that is used while the game is currently in play
	class GameState : public State
	{
		private:
			// Member variables
			GameDataRef data;
			sf::Sprite background;
			//sf::Sprite pauseButton;
			//sf::Sprite gridSprite;
			//sf::Sprite gridPieces[GRID_HEIGHT * GRID_WIDTH];

			//int gridArray[GRID_HEIGHT * GRID_WIDTH];

			//int turn;
			//int gameState;

		public:
			// Constructor
			GameState(GameDataRef dataIn);

			// Destructor
			~GameState();

			// Member functions
			void init();
			void handleInput();
			void update(float deltaTimeIn);
			void draw(float deltaTimeIn);

			// Functions responsible for scanning the grid for search targets
			void solve();
			void scanHorizontally();
			void scanVertically();
			void scanDiagonallyDown();
			void scanDiagonallyDownTop();
			void scanDiagonallyDownBottom();
			void scanDiagonallyUp();
			void scanDiagonallyUpTop();
			void scanDiagonallyUpBottom();
	};
}

#endif