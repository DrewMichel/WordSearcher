#ifndef DREW_SPLASH_STATE_H
#define DREW_SPLASH_STATE_H

#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Drewski
{
	class SplashState : public State
	{
		public:
			SplashState(GameDataRef dataIn);
			~SplashState();

			void init();

			void handleInput();
			void update(float deltaTimeIn);
			void draw(float deltaTimeIn);

		private:
			GameDataRef data;

			sf::Clock clock;
			sf::Sprite background;
	};
}

#endif