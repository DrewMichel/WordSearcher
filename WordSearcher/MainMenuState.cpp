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
		this->data->assetManager.loadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->data->assetManager.loadTexture("Play Button", MAIN_MENU_PLAY_BUTTON);
		this->data->assetManager.loadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->data->assetManager.loadTexture("Game Title", MAIN_MENU_TITLE_PATH);

		this->background.setTexture(this->data->assetManager.getTexture("Background"));
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

	void MainMenuState::draw(float deltaTimeIn)
	{
		this->data->window.clear();

		this->data->window.draw(this->background);
		this->data->window.draw(this->playButton);
		this->data->window.draw(this->playButtonOuter);
		this->data->window.draw(this->title);

		this->data->window.display();
	}
}