// Created by: Andrew Steven Michel
// Date Created: May 2018

// IMPORTED PACKAGES:
#include "MainMenuState.h"
#include <sstream>
#include <iostream>
#include "Definitions.h"
#include "GameState.h"

// Namespace declaration
namespace Drewski
{
	// Constructor
	MainMenuState::MainMenuState(GameDataRef dataIn) : data(dataIn)
	{

	}

	// Destructor
	MainMenuState::~MainMenuState()
	{

	}

	// Function responsible for initializing the state
	void MainMenuState::init()
	{
		//this->data->assetManager.loadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->data->assetManager.loadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		this->data->assetManager.loadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->data->assetManager.loadTexture("Game Title", MAIN_MENU_TITLE_PATH);

		//this->background.setTexture(this->data->assetManager.getTexture("Background"));
		this->playButton.setTexture(this->data->assetManager.getTexture("Play Button"));
		this->playButtonOuter.setTexture(this->data->assetManager.getTexture("Play Button Outer"));
		this->title.setTexture(this->data->assetManager.getTexture("Game Title"));

		this->playButton.setPosition(SCREEN_WIDTH / 2 - (this->playButton.getGlobalBounds().width / 2), SCREEN_HEIGHT / 2 - (this->playButton.getGlobalBounds().height / 2));

		this->playButtonOuter.setPosition(SCREEN_WIDTH / 2 - (this->playButtonOuter.getGlobalBounds().width / 2), SCREEN_HEIGHT / 2 - (this->playButtonOuter.getGlobalBounds().height / 2));

		this->title.setPosition(SCREEN_WIDTH / 2 - (this->title.getGlobalBounds().width / 2), this->title.getGlobalBounds().height * 0.1);
	}

	// Function responsible for handling input on the state
	void MainMenuState::handleInput()
	{
		// Declares event variable used to manage events
		sf::Event sfEvent;

		// Loops while the event has unprocessed events
		while (this->data->window.pollEvent(sfEvent))
		{
			// Closes the window based on the event's type
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}

			// Determines if the play button has been clicked
			if (this->data->inputManager.isSpriteClicked(this->playButton, sf::Mouse::Left, this->data->window))
			{
				//std::cout << "Go to Game Screen" << std::endl;

				// If the play button has been clicked, push a GameState onto the state machine
				this->data->machine.addState(StateRef(new GameState(data)), true);
			}
		}
	}

	// Function responsible for updating the state
	void MainMenuState::update(float deltaTimeIn)
	{

	}

	// Lazy global variable
	int backgroundAnimationCounter = 0;

	// Function responsible for drawing the state
	void MainMenuState::draw(float deltaTimeIn)
	{
		// Clears the window
		this->data->window.clear();

		// Increments counter
		backgroundAnimationCounter++;

		// Resets counter if greater than 255
		if (backgroundAnimationCounter > 255)
		{
			backgroundAnimationCounter = 0;
		}

		// TODO: MOVE TO MAIN MENU, USE ORBIT IN GAME
		int number;

		// Creates an one dimensional array which is treated as a two dimensional array that stores pixel colors
		sf::Uint8 *pixels = new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4];

		// Iterates based on screen height
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			// Iterates based on screen width
			for (int x = 0; x < SCREEN_WIDTH; x++)
			{
				// position index
				number = 4 * ((y * SCREEN_WIDTH) + x);

				// RED
				if (backgroundAnimationCounter + ((x / (float)SCREEN_WIDTH * 255)) <= 255)
				{
					pixels[number] = backgroundAnimationCounter + ((x / (float)SCREEN_WIDTH * 255));
				}
				else
				{
					pixels[number] = ((x / (float)SCREEN_WIDTH * 255)) - backgroundAnimationCounter;
				}

				pixels[number + 1] = (x / ((float)SCREEN_WIDTH * 5) * 255); // GREEN
				pixels[number + 2] = (x / ((float)SCREEN_WIDTH * 5) * 255); // BLUE
				pixels[number + 3] = 255; // ALPHA
			}
		}

		// Declares and creates an image, texture, and sprite based on pixel array
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;

		image.create(SCREEN_WIDTH, SCREEN_HEIGHT, pixels);
		texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		// Draws the sprite
		this->data->window.draw(sprite);

		// Deletes the pixel array
		delete[] pixels;

		//this->data->window.draw(this->background);

		// Draws elements
		this->data->window.draw(this->playButton);
		this->data->window.draw(this->playButtonOuter);
		this->data->window.draw(this->title);

		// Updates or displays the window
		this->data->window.display();
	}
}