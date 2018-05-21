#ifndef DREW_GAME_OVER_STATE_H
#define DREW_GAME_OVER_STATE_H

// IMPORTED PACKAGES:
#include "Game.h"
#include "State.h"

// Namespace declaration
namespace Drewski
{
	// GameOverState that is displayed when the user loses. Currently unused.
	class GameOverState : public State
	{
		private:
			// Member variables
			GameDataRef data;
			sf::Sprite retryButton;
			sf::Sprite homeButton;

		public:
			// Constructor
			GameOverState(GameDataRef dataIn);

			// Destructor
			~GameOverState();

			// Member functions
			void init();
			void handleInput();
			void update(float deltaTimeIn);
			void draw(float deltaTimeIn);
	};
}

#endif