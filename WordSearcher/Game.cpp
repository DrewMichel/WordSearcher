#include "Game.h"
#include "SplashState.h"

namespace Drewski
{
	Game::Game(int width, int height, string title, vector<string> gridIn, vector<string> searchIn)
	{
		data->grid = gridIn;
	
		// generate searches
		for (int i = 0; i < searchIn.size(); i++)
		{
			string san = WordSanitizer::sanitize(searchIn[i]);

			data->parseSearch[san] = searchIn[i];
			data->parseSearch[WordSanitizer::reverse(san)] = searchIn[i];

			data->originalSearch[searchIn[i]] = SearchWord(searchIn[i]);
		}

		data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		//data->window.setFramerateLimit(60);

		data->machine.addState(StateRef(new SplashState(this->data)));

		this->run(); // could remove if desired to choose run activation
	}

	void Game::run()
	{
		float newTime, frameTime, interpolation;
		float currentTime = this->clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (this->data->window.isOpen())
		{
			this->data->machine.processStateChanges();

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
				this->data->machine.getActivateState()->handleInput();
				this->data->machine.getActivateState()->update(DELTA_TIME);

				accumulator -= DELTA_TIME;
			}

			interpolation = accumulator / DELTA_TIME;

			this->data->machine.getActivateState()->draw(interpolation);
		}
	}
}