// Created by: Andrew Steven Michel
// Date Created: May 2018
#ifndef DREW_SPLASH_STATE_H
#define DREW_SPLASH_STATE_H

// IMPORTED PACKAGES:
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

// Namespace declaration
namespace Drewski
{
	// Class that is used to display the splash screen
	class SplashState : public State
	{
		private:
			// Member variables
			GameDataRef data;

			sf::Clock clock;
			sf::Sprite background;

		public:
			// Constructor
			SplashState(GameDataRef dataIn);

			// Destructor
			~SplashState();

			// Member functions
			void init();

			void handleInput();
			void update(float deltaTimeIn);
			void draw(float deltaTimeIn);
	};
}

#endif