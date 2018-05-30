// Created by: Andrew Steven Michel
// Date Created: May 2018
#ifndef DREW_PAUSE_STATE_H
#define DREW_PAUSE_STATE_H

// IMPORTED PACKAGES:
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

// Namespace declaration
namespace Drewski
{
	// Class that is used to display the game while paused. Currently unused
	class PauseState : public State
	{
		private:
			// Member variables
			GameDataRef data;
			sf::Sprite background;
			sf::Sprite resumeButton;
			sf::Sprite homeButton;

		public:
			// Constructor
			PauseState(GameDataRef dataIn);

			// Destructor
			~PauseState();

			// Member functions
			void init();
			void handleInput();
			void update(float deltaTimeIn);
			void draw(float deltaTimeIn);
	};
}

#endif