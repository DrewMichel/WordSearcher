#include "GameState.h"

#include <sstream>
#include <iostream>
#include "Definitions.h"
#include "PauseState.h"
#include "GameOverState.h"

namespace Drewski
{
	GameState::GameState(GameDataRef dataIn) : data(dataIn)
	{

	}

	GameState::~GameState()
	{

	}

	void GameState::init()
	{
		gameState = STATE_PLAYING;
		turn = PLAYER_PIECE;

		this->data->assetManager.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->data->assetManager.loadTexture("Pause Button", PAUSE_BUTTON);

		background.setTexture(this->data->assetManager.getTexture("Game Background"));
		pauseButton.setTexture(this->data->assetManager.getTexture("Pause Button"));

		pauseButton.setPosition(this->data->window.getSize().x - pauseButton.getLocalBounds().width, pauseButton.getPosition().y);
	}

	void GameState::handleInput()
	{
		sf::Event sfEvent;

		while (this->data->window.pollEvent(sfEvent))
		{
			if (sf::Event::Closed == sfEvent.type)
			{
				this->data->window.close();
			}

			if (this->data->inputManager.isSpriteClicked(this->pauseButton, sf::Mouse::Left, this->data->window))
			{
				//std::cout << "Pause the Game" << std::endl;
				this->data->machine.addState(StateRef(new PauseState(data)), false);

				//this->data->machine.addState(StateRef(new GameOverState(data)), true);
			}
		}
	}

	void GameState::update(float deltaTimeIn)
	{

	}

	void GameState::draw(float deltaTimeIn)
	{
		this->data->window.clear();

		this->data->window.draw(this->background);
		this->data->window.draw(this->pauseButton);

		this->data->window.display();
	}
}