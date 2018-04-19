#include <sstream>
#include <iostream>

#include "PauseState.h"
#include "Definitions.h"
#include "GameState.h"
#include "MainMenuState.h"

namespace Drewski
{
	PauseState::PauseState(GameDataRef dataIn) : data(dataIn)
	{

	}

	PauseState::~PauseState()
	{

	}

	void PauseState::init()
	{
		this->data->assetManager.loadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
		this->data->assetManager.loadTexture("Resume Button", RESUME_BUTTON);
		this->data->assetManager.loadTexture("Home Button", HOME_BUTTON);

		this->background.setTexture(this->data->assetManager.getTexture("Pause Background"));
		this->resumeButton.setTexture(this->data->assetManager.getTexture("Resume Button"));
		this->homeButton.setTexture(this->data->assetManager.getTexture("Home Button"));

		this->resumeButton.setPosition((this->data->window.getSize().x / 2) - (this->resumeButton.getLocalBounds().width / 2), (this->data->window.getSize().y / 3) - (this->resumeButton.getLocalBounds().height / 2) );
		this->homeButton.setPosition((this->data->window.getSize().x / 2) - (this->homeButton.getLocalBounds().width / 2), (this->data->window.getSize().y / 3 * 2) - (this->homeButton.getLocalBounds().height / 2));
	}

	void PauseState::handleInput()
	{
		sf::Event sfEvent;

		while (this->data->window.pollEvent(sfEvent))
		{
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}
			
			if (this->data->inputManager.isSpriteClicked(this->resumeButton, sf::Mouse::Left, this->data->window))
			{
				//std::cout << "Go to Game Screen" << std::endl;
				this->data->machine.removeState();
			}

			if (this->data->inputManager.isSpriteClicked(this->homeButton, sf::Mouse::Left, this->data->window))
			{
				this->data->machine.removeState();
				this->data->machine.addState(StateRef(new MainMenuState(data)), true);
			}
		}
	}

	void PauseState::update(float deltaTimeIn)
	{

	}

	void PauseState::draw(float deltaTimeIn)
	{
		this->data->window.clear();
		
		this->data->window.draw(this->background);
		this->data->window.draw(this->resumeButton);
		this->data->window.draw(this->homeButton);
		
		this->data->window.display();
	}
}