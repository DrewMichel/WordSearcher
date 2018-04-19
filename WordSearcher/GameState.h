#ifndef DREW_GAME_STATE_H
#define DREW_GAME_STATE_H

#include "Game.h"

namespace Drewski
{
	class GameState : public State
	{
	private:
		GameDataRef data;
		sf::Sprite background;
		sf::Sprite pauseButton;

		int turn;
		int gameState;

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