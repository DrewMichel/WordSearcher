#ifndef DREW_GAME_H
#define DREW_GAME_H

#include <memory>
#include <string>

#include <SFML\Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

using namespace std;

namespace Drewski
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assetManager;
		InputManager inputManager;
	};

	typedef shared_ptr<GameData> GameDataRef;

	class Game
	{
		private:
			const float DELTA_TIME = 1.0f / 60.0f; // Could allow modification based on game design
			sf::Clock clock;
			GameDataRef data = make_shared<GameData>();

			void run();
		public:
			Game(int width, int height, string title);
		
	};
}

#endif