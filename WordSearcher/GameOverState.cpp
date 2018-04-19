#include "GameOverState.h"
#include "MainMenuState.h"

#include <sstream>
#include <iostream>
#include "Definitions.h"
#include "GameState.h"

namespace Drewski
{
	GameOverState::GameOverState(GameDataRef dataIn) : data(dataIn)
	{

	}

	GameOverState::~GameOverState()
	{

	}

	void GameOverState::init()
	{
		this->data->assetManager.loadTexture("Retry Button", RETRY_BUTTON);
		this->data->assetManager.loadTexture("Home Button", HOME_BUTTON);
	

		this->retryButton.setTexture(this->data->assetManager.getTexture("Retry Button"));
		this->homeButton.setTexture(this->data->assetManager.getTexture("Home Button"));

		this->retryButton.setPosition((this->data->window.getSize().x / 2) - (this->retryButton.getLocalBounds().width / 2), (this->data->window.getSize().y / 3) - (this->retryButton.getLocalBounds().height / 2));
		this->homeButton.setPosition((this->data->window.getSize().x / 2) - (this->homeButton.getLocalBounds().width / 2), (this->data->window.getSize().y / 3 * 2) - (this->homeButton.getLocalBounds().height / 2));
	}

	void GameOverState::handleInput()
	{
		sf::Event sfEvent;

		while (this->data->window.pollEvent(sfEvent))
		{
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}

			if (this->data->inputManager.isSpriteClicked(this->retryButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.addState(StateRef(new GameState(data)), true);
			}

			if (this->data->inputManager.isSpriteClicked(this->homeButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.addState(StateRef(new MainMenuState(data)), true);
			}
		}
	}

	void GameOverState::update(float deltaTimeIn)
	{

	}

	void GameOverState::draw(float deltaTimeIn)
	{
		this->data->window.clear(sf::Color::Red);

		this->data->window.draw(this->retryButton);
		this->data->window.draw(this->homeButton);

		this->data->window.display();
	}
}