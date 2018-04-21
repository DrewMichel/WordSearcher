#include "MainMenuState.h"

#include <sstream>
#include <iostream>
#include "Definitions.h"
#include "GameState.h"

namespace Drewski
{
	MainMenuState::MainMenuState(GameDataRef dataIn) : data(dataIn)
	{

	}

	MainMenuState::~MainMenuState()
	{

	}

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

	void MainMenuState::handleInput()
	{
		sf::Event sfEvent;

		while (this->data->window.pollEvent(sfEvent))
		{
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}

			if (this->data->inputManager.isSpriteClicked(this->playButton, sf::Mouse::Left, this->data->window))
			{
				//std::cout << "Go to Game Screen" << std::endl;
				this->data->machine.addState(StateRef(new GameState(data)), true);
			}
		}
	}

	void MainMenuState::update(float deltaTimeIn)
	{

	}


	int backgroundAnimationCounter = 0;

	void MainMenuState::draw(float deltaTimeIn)
	{
		this->data->window.clear();

		backgroundAnimationCounter++;

		if (backgroundAnimationCounter > 255)
		{
			backgroundAnimationCounter = 0;
		}

		// TODO: MOVE TO MAIN MENU, USE ORBIT IN GAME
		int number;

		sf::Uint8 *pixels = new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4];
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			for (int x = 0; x < SCREEN_WIDTH; x++)
			{
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

		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;

		image.create(SCREEN_WIDTH, SCREEN_HEIGHT, pixels);
		texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		this->data->window.draw(sprite);

		delete[] pixels;

		//this->data->window.draw(this->background);
		this->data->window.draw(this->playButton);
		this->data->window.draw(this->playButtonOuter);
		this->data->window.draw(this->title);

		this->data->window.display();
	}
}