// Created by: Andrew Steven Michel
// Date Created: May 2018

// IMPORTED PACKAGES
#include <sstream>
#include <iostream>
#include "SplashState.h"
#include "Definitions.h"
#include "MainMenuState.h"

// Namespace usage which allows the direct use of declarations
using namespace std;

// Namespace declaration
namespace Drewski
{
	// Constructor
	SplashState::SplashState(GameDataRef dataIn) : data(dataIn)
	{

	}

	// Destructor
	SplashState::~SplashState()
	{

	}

	// Function responsible for initializing the state
	void SplashState::init()
	{
		this->data->assetManager.loadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);

		background.setTexture(this->data->assetManager.getTexture("Splash State Background"));
	}

	// Function responsible for handling input on the state
	void SplashState::handleInput()
	{
		// Event variable used to handle events
		sf::Event sfEvent;

		// Loops while events remain unprocessed
		while (this->data->window.pollEvent(sfEvent))
		{
			// Closes the window based on event type
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}
		}
	}

	// Function reponsible for updating the state
	void SplashState::update(float deltaTimeIn)
	{
		// After time has elapsed, pushes a main menu state onto the state machine
		if (this->clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			//std::cout << "Go to main menu" << endl;
			// Pushes main menu state
			this->data->machine.addState(StateRef(new MainMenuState(data)), true);
		}
	}

	// Function responsible for drawing the state
	void SplashState::draw(float deltaTimeIn)
	{
		// Clears the screen by making all pixels red
		this->data->window.clear(sf::Color::Red);

		// Draws background image
		this->data->window.draw(this->background);

		// Displays or updates the window
		this->data->window.display();
	}
}

