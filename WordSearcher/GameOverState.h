#ifndef DREW_GAME_OVER_STATE_H
#define DREW_GAME_OVER_STATE_H

#include "Game.h"
#include "State.h"

namespace Drewski
{
	class GameOverState : public State
	{
	private:
		GameDataRef data;
		sf::Sprite retryButton;
		sf::Sprite homeButton;

	public:
		GameOverState(GameDataRef dataIn);
		~GameOverState();

		void init();
		void handleInput();
		void update(float deltaTimeIn);
		void draw(float deltaTimeIn);
	};
}

#endif