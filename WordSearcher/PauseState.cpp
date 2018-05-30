// Created by: Andrew Steven Michel
// Date Created: May 2018

// IMPORTED PACKAGES
#include <sstream>
#include <iostream>
#include "PauseState.h"
#include "Definitions.h"
#include "GameState.h"
#include "MainMenuState.h"

// Namespace declaration
namespace Drewski
{
	// Constructor
	PauseState::PauseState(GameDataRef dataIn) : data(dataIn)
	{

	}

	// Destructor
	PauseState::~PauseState()
	{

	}

	// Function responsible for initializing the state
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

	// Function responsible for handling input on the state
	void PauseState::handleInput()
	{
		// Event variable used to manage events
		sf::Event sfEvent;

		// Loops while the event has unprocessed events
		while (this->data->window.pollEvent(sfEvent))
		{
			// Closes the window based on event type
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}
			
			// Determines if the resume or home buttons have been clicked
			if (this->data->inputManager.isSpriteClicked(this->resumeButton, sf::Mouse::Left, this->data->window))
			{
				//std::cout << "Go to Game Screen" << std::endl;
				// Removes paused state
				this->data->machine.removeState();
			}

			if (this->data->inputManager.isSpriteClicked(this->homeButton, sf::Mouse::Left, this->data->window))
			{
				// Removes paused state and adds a main menu state
				this->data->machine.removeState();
				this->data->machine.addState(StateRef(new MainMenuState(data)), true);
			}
		}
	}
	
	// Function responsible for updating the state
	void PauseState::update(float deltaTimeIn)
	{

	}

	// Function responsible for drawing the state
	void PauseState::draw(float deltaTimeIn)
	{
		this->data->window.clear();
		
		this->data->window.draw(this->background);
		this->data->window.draw(this->resumeButton);
		this->data->window.draw(this->homeButton);
		
		this->data->window.display();
	}
}