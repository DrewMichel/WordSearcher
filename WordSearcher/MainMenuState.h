#ifndef DREW_MAIN_MENU_STATE_H
#define DREW_MAIN_MENU_STATE_H

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Drewski
{
	class MainMenuState : public State
	{
		private:
			GameDataRef data;
			sf::Sprite background;
			sf::Sprite playButton;
			sf::Sprite playButtonOuter;
			sf::Sprite title;

		public:
			MainMenuState(GameDataRef dataIn);
			~MainMenuState();

			void init();
			void handleInput();
			void update(float deltaTimeIn);
			void draw(float deltaTimeIn);
	};
}

#endif