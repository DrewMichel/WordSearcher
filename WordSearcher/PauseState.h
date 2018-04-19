#ifndef DREW_PAUSE_STATE_H
#define DREW_PAUSE_STATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Drewski
{
	class PauseState : public State
	{
	private:
		GameDataRef data;
		sf::Sprite background;
		sf::Sprite resumeButton;
		sf::Sprite homeButton;

	public:
		PauseState(GameDataRef dataIn);
		~PauseState();

		void init();
		void handleInput();
		void update(float deltaTimeIn);
		void draw(float deltaTimeIn);
	};
}

#endif