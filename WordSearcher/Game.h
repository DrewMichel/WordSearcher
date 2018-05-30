// Created by: Andrew Steven Michel
// Date Created: May 2018
#ifndef DREW_GAME_H
#define DREW_GAME_H

#include <memory>
#include <string>

// IMPORTED PACKAGES:
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include "SearchWord.h"

// Namespace usage which allows the direct use of declarations
using namespace std;

// Namespace declaration
namespace Drewski
{
	// Struct that stores game data which is passed between states
	struct GameData
	{
		public:
			StateMachine machine;
			sf::RenderWindow window;
			AssetManager assetManager;
			InputManager inputManager;
			vector<string> grid;
			unordered_map<string, string> parseSearch;
			unordered_map<string, SearchWord> originalSearch;
	};

	// Creates a type definition for a shared pointer of GameData as GameDataRef
	typedef shared_ptr<GameData> GameDataRef;

	// Topmost class of the game which initializes primary systems
	class Game
	{
		private:
			// Member variables
			const float DELTA_TIME = 1.0f / 60.0f; // Could allow modification based on game design
			sf::Clock clock;
			GameDataRef data = make_shared<GameData>();

			// Member functions
			void run();
		public:
			// Constructor
			Game(int width, int height, string title, vector<string> gridIn = vector<string>(), vector<string> searchIn = vector<string>());
		
	};
}

#endif