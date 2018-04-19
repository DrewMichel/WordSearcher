#include <sstream>
#include <iostream>

#include "SplashState.h"
#include "Definitions.h"
#include "MainMenuState.h"

using namespace std;

namespace Drewski
{
	SplashState::SplashState(GameDataRef dataIn) : data(dataIn)
	{

	}

	SplashState::~SplashState()
	{

	}

	void SplashState::init()
	{
		this->data->assetManager.loadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

		background.setTexture(this->data->assetManager.getTexture("Splash State Background"));
	}

	void SplashState::handleInput()
	{
		sf::Event sfEvent;

		while (this->data->window.pollEvent(sfEvent))
		{
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}
		}
	}

	void SplashState::update(float deltaTimeIn)
	{
		if (this->clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			//std::cout << "Go to main menu" << endl;
			this->data->machine.addState(StateRef(new MainMenuState(data)), true);
		}
	}

	void SplashState::draw(float deltaTimeIn)
	{
		this->data->window.clear(sf::Color::Red);

		this->data->window.draw(this->background);

		this->data->window.display();
	}
}

