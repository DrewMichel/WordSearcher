// Created by: Andrew Steven Michel
// Date Created: May 2018
#ifndef DREW_MAIN_MENU_STATE_H
#define DREW_MAIN_MENU_STATE_H

// IMPORTED PACKAGES:
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

// Namespace declaration
namespace Drewski
{
	// Class that is used to display the main menu
	class MainMenuState : public State
	{
		private:
			// Member variables
			GameDataRef data;
			sf::Sprite background;
			sf::Sprite playButton;
			sf::Sprite playButtonOuter;
			sf::Sprite title;

		public:
			// Constructor
			MainMenuState(GameDataRef dataIn);

			// Destructor
			~MainMenuState();

			// Member functions
			void init();
			void handleInput();
			void update(float deltaTimeIn);
			void draw(float deltaTimeIn);
	};
}

#endif