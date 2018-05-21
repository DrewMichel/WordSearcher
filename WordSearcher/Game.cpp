// IMPORTED PACKAGES:
#include "Game.h"
#include "SplashState.h"

// Namespace declaration
namespace Drewski
{
	// Constructor
	Game::Game(int width, int height, string title, vector<string> gridIn, vector<string> searchIn)
	{
		// Stores the grid data into member variable
		data->grid = gridIn;
	
		// Generates search words by sanitizing and adding the sanitized
		// and a reversed version into an unordered_map
		// and stores the original search word into another unordered_map
		for (int i = 0; i < searchIn.size(); i++)
		{
			// Sanitizes search word
			string san = WordSanitizer::sanitize(searchIn[i]);

			// Stores the sanitized word and its reverse into an unordered_map
			data->parseSearch[san] = searchIn[i];
			data->parseSearch[WordSanitizer::reverse(san)] = searchIn[i];

			// Stores the original search word into an unordered_map
			data->originalSearch[searchIn[i]] = SearchWord(searchIn[i]);
		}

		// Generates the SFML window
		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		//data->window.setFramerateLimit(60);

		// Pushes the splash state onto the state machine
		data->machine.addState(StateRef(new SplashState(this->data)));

		// Begins the primary game loop
		this->run(); // could remove if desired to choose run activation and make public
	}

	// Function that controls the primary game loop
	void Game::run()
	{
		// Declares variables
		float newTime, frameTime, interpolation;
		float currentTime = this->clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		// Loops while the window is open
		while (this->data->window.isOpen())
		{
			// Processes states on the state machine
			this->data->machine.processStateChanges();

			// Determines time passage between updates
			newTime = this->clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= DELTA_TIME)
			{
				// Handles input and updates on the state machines
				this->data->machine.getActivateState()->handleInput();
				this->data->machine.getActivateState()->update(DELTA_TIME);

				accumulator -= DELTA_TIME;
			}

			interpolation = accumulator / DELTA_TIME;

			// Draws based on the state machine's top most state
			this->data->machine.getActivateState()->draw(interpolation);
		}
	}
}