#include "GameState.h"

#include <sstream>
#include <iostream>
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
		this->data->assetManager.loadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);

		this->data->assetManager.loadTexture("X Piece", X_PIECE_FILEPATH);
		this->data->assetManager.loadTexture("O Piece", O_PIECE_FILEPATH);

		background.setTexture(this->data->assetManager.getTexture("Game Background"));
		pauseButton.setTexture(this->data->assetManager.getTexture("Pause Button"));
		gridSprite.setTexture(this->data->assetManager.getTexture("Grid Sprite"));

		pauseButton.setPosition(this->data->window.getSize().x - pauseButton.getLocalBounds().width, pauseButton.getPosition().y);
		gridSprite.setPosition((SCREEN_WIDTH / 2) - (gridSprite.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (gridSprite.getGlobalBounds().height / 2));

		initGridPieces();

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				gridArray[(y * GRID_HEIGHT) + x ] = EMPTY_PIECE;
			}
		}
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
			else if (this->data->inputManager.isSpriteClicked(this->gridSprite, sf::Mouse::Left, this->data->window))
			{
				this->checkAndPlacePiece();
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
		this->data->window.draw(gridSprite);

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				this->data->window.draw(gridPieces[(y * GRID_HEIGHT) + x]);
			}
		}

		this->data->window.display();
	}

	void GameState::initGridPieces()
	{
		sf::Vector2u tempSpriteSize = this->data->assetManager.getTexture("X Piece").getSize();

		for (int y = 0; y < GRID_HEIGHT; y++)
		{
			for (int x = 0; x < GRID_WIDTH; x++)
			{
				gridPieces[(y * GRID_HEIGHT) + x].setTexture(this->data->assetManager.getTexture("X Piece"));
				gridPieces[(y * GRID_HEIGHT) + x].setPosition(gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);

				//std::cout << x << ", " << y << " : " << gridPieces[y][x].getPosition().x << ", " << gridPieces[y][x].getPosition().y << endl;

				gridPieces[(y * GRID_HEIGHT) + x].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::checkAndPlacePiece()
	{
		
		sf::Vector2i touchPoint = this->data->inputManager.getMousePosition(this->data->window);
		sf::FloatRect gridSize = gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);
		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / GRID_WIDTH, gridSize.height / GRID_HEIGHT);

		int column, row;

		for (int x = GRID_WIDTH - 1; x >= 0 ; x--)
		{
			if (gridLocalTouchPos.x < gridSectionSize.x * (x + 1))
			{
				column = x;
			}
		}

		for (int y = GRID_HEIGHT - 1; y >= 0; y--)
		{
			if (gridLocalTouchPos.y < gridSectionSize.y * (y + 1))
			{
				row = y;
			}
		}

		if (gridArray[(row * GRID_HEIGHT ) + column] == EMPTY_PIECE )
		{
			gridArray[(row * GRID_HEIGHT) + column] = turn;

			if (PLAYER_PIECE == turn)
			{
				gridPieces[(row * GRID_HEIGHT) + column].setTexture(this->data->assetManager.getTexture("X Piece"));

				turn = AI_PIECE;
			}
			else if (AI_PIECE == turn)
			{
				gridPieces[(row * GRID_HEIGHT) + column].setTexture(this->data->assetManager.getTexture("O Piece"));

				turn = PLAYER_PIECE;
			}

			gridPieces[(row * GRID_HEIGHT) + column].setColor(sf::Color(255, 255, 255, 255));
		}
		
	}
}