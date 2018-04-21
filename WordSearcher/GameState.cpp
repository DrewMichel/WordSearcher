#include "GameState.h"

#include <sstream>
#include <iostream>
#include "PauseState.h"
#include "GameOverState.h"
#include "PerlinNoise.h"
#include <chrono>

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

		this->data->assetManager.loadFont("courier new bold", FONT_COURIER_NEW_BOLD_FILEPATH);
		this->data->assetManager.loadTexture("Pause Button", PAUSE_BUTTON);
		/*
		sf::Text text;
		text.setFont(this->data->assetManager.getFont("arial"));
		text.setString("SAMPLE TEXT");
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(24);

		this->data->assetManager.addText("TEST", text);
		*/

		for(int i = 0; i < data->grid.size(); i++)
		{
			sf::Text text;
			text.setFont(this->data->assetManager.getFont("courier new bold"));
			text.setString(WordSanitizer::smudge(data->grid[i]));
			text.setFillColor(sf::Color(255, 215, 0, 255));
			text.setCharacterSize(25);

			text.setPosition(text.getPosition().x + 25, text.getPosition().y +  25 + (i * 30));

			this->data->assetManager.addText("GRID" + to_string(i), text);
		}

		pauseButton.setTexture(this->data->assetManager.getTexture("Pause Button"));
		pauseButton.setPosition(this->data->window.getSize().x - pauseButton.getLocalBounds().width, pauseButton.getPosition().y);
		//pauseButton.setColor(sf::Color(0, 0, 0, 255));
#if 0
		turn = PLAYER_PIECE;

		this->data->assetManager.loadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->data->assetManager.loadTexture("Pause Button", PAUSE_BUTTON);
		this->data->assetManager.loadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);

		this->data->assetManager.loadTexture("X Piece", X_PIECE_FILEPATH);
		this->data->assetManager.loadTexture("O Piece", O_PIECE_FILEPATH);

		this->data->assetManager.loadTexture("X Piece Won", X_PIECE_WON_FILEPATH);
		this->data->assetManager.loadTexture("O Piece Won", O_PIECE_WON_FILEPATH);

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
#endif
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

			/*
			if (sf::Event::TextEntered == sfEvent.type)
			{
				if (sfEvent.text.unicode < 128)
				{
					cout << static_cast<char>(sfEvent.text.unicode) << endl;
				}
			}
			*/

			// display to screen string (RAW)
			// if that text is click,
			// getString (RAW) and use it as index in unordered_map<string (RAW), SearchWord)>
			// toggle SearchWord isDisplaying
			// In draw function, iterate through and outline displaying searchwords based on x1, y1, x2, y2, coordinates
			for (auto iterator = data->assetManager.getTextMap().begin(); iterator != data->assetManager.getTextMap().end(); iterator++)
			{
				if (data->inputManager.isTextClicked(iterator->second, sf::Mouse::Left, this->data->window))
				{
					string out = iterator->second.getString();
					cout << out << endl;
				}
			}

#if 0
			if (this->data->inputManager.isSpriteClicked(this->pauseButton, sf::Mouse::Left, this->data->window))
			{
				//std::cout << "Pause the Game" << std::endl;
				this->data->machine.addState(StateRef(new PauseState(data)), false);

				//this->data->machine.addState(StateRef(new GameOverState(data)), true);
			}
			else if (this->data->inputManager.isSpriteClicked(this->gridSprite, sf::Mouse::Left, this->data->window))
			{
				if (gameState == STATE_PLAYING)
				{
					this->checkAndPlacePiece();
				}
				
			}
#endif
		}
	}

	void GameState::update(float deltaTimeIn)
	{

	}

	void GameState::draw(float deltaTimeIn)
	{
		this->data->window.clear(sf::Color::Black);
		//this->data->window.clear();
#if 0
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
#endif
#if 0
		backgroundAnimationCounter++;
		if (backgroundAnimationCounter > 60)
		{
			this->data->window.clear();
			backgroundAnimationCounter = 0;

			PerlinNoise color;

			double speed = 0.05f, z = 0.5f;
			int number;
			int random = rand();

			sf::Uint8 *pixels = new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4];
			for (int y = 0; y < SCREEN_HEIGHT; y++)
			{
				for (int x = 0; x < SCREEN_WIDTH; x++)
				{
					number = 4 * ((y * SCREEN_WIDTH) + x);
					pixels[number] = color.noise(x * speed, y * speed, z) * 255; // RED
					pixels[number + 1] = color.noise(x * speed + random, y * speed + random, z) * 255; // GREEN
					pixels[number + 2] = color.noise(x * speed + random * random, y * speed + random * random, z) * 255; // BLUE
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
		}
#endif

#if 0
		if (backgroundAnimationCounter > 255)
		{
			backgroundAnimationCounter = 0;
		}

		cout << "COUNTER: " << backgroundAnimationCounter << endl;

		backgroundAnimationCounter++;
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
#endif

		//this->data->assetManager.getPerlin().update();

		//this->data->window.draw(this->data->assetManager.getPerlin().getSprite());
		
		
		//this->data->window.draw(this->background);

		sf::Image centerImage;
		sf::Sprite centerSprite;
		sf::Texture centerTexture;

		centerImage.create(30, SCREEN_HEIGHT, sf::Color(255, 255, 255, 255));

		centerTexture.create(30, SCREEN_HEIGHT);
		centerTexture.loadFromImage(centerImage);

		centerSprite.setTexture(centerTexture);

		centerSprite.setPosition(SCREEN_WIDTH / 2, centerSprite.getPosition().y);

		this->data->window.draw(centerSprite);

		this->data->window.draw(this->pauseButton);

		for (auto iterator = this->data->assetManager.getTextMap().begin(); iterator != this->data->assetManager.getTextMap().end(); iterator++)
		{
			this->data->window.draw(iterator->second);
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

		cout << "GAME STATE: " << gameState << endl;
		if (gridArray[(row * GRID_HEIGHT ) + column] == EMPTY_PIECE && gameState == STATE_PLAYING)
		{
			gridArray[(row * GRID_HEIGHT) + column] = turn;

			if (PLAYER_PIECE == turn)
			{
				gridPieces[(row * GRID_HEIGHT) + column].setTexture(this->data->assetManager.getTexture("X Piece"));

				this->checkPlayerHasWon(turn);

				turn = AI_PIECE;
			}
			else if (AI_PIECE == turn)
			{
				gridPieces[(row * GRID_HEIGHT) + column].setTexture(this->data->assetManager.getTexture("O Piece"));

				this->checkPlayerHasWon(turn);

				turn = PLAYER_PIECE;
			}

			gridPieces[(row * GRID_HEIGHT) + column].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::checkPlayerHasWon(int turn)
	{
		vector<int> winningIndices;

		checkHorizontalMatch(turn, winningIndices);
		checkVerticalMatch(turn, winningIndices);
		checkDiagonalDownMatch(turn, winningIndices);
		checkDiagonalUpMatch(turn, winningIndices);
		checkDrawMatch();

		if ((gameState == STATE_DRAW || gameState == STATE_LOSE || gameState == STATE_WON) && ((winningIndices.size() / 2) >= WIN_REQUIREMENT))
		{
			if (gameState == STATE_WON)
			{
				for (int i = 0; i < winningIndices.size(); i+=2)
				{
					gridPieces[(winningIndices[i] * GRID_HEIGHT) + winningIndices[i + 1]].setTexture(this->data->assetManager.getTexture("X Piece Won"));
					cout << winningIndices[i + 1] << ", " << (winningIndices[i]) << endl;
				}
			}
			else if (gameState == STATE_LOSE)
			{
				for (int i = 0; i < winningIndices.size(); i+=2)
				{
					gridPieces[(winningIndices[i] * GRID_HEIGHT) + winningIndices[i + 1]].setTexture(this->data->assetManager.getTexture("O Piece Won"));
				}
			}
		}
	}

	// x x x
	void GameState::checkHorizontalMatch(int pieceToCheck, vector<int>& winningIndices)
	{
		int pieceMatches = 0;
		bool ongoing = true;

		if (gameState == STATE_PLAYING)
		{
			for (int y = 0; y < GRID_HEIGHT && ongoing; y++)
			{
				pieceMatches = 0;
				winningIndices.clear();

				for (int x = 0; x < GRID_WIDTH && ongoing; x++)
				{
					if (gridArray[(y * GRID_HEIGHT) + x] == pieceToCheck)
					{
						pieceMatches++;
						winningIndices.push_back(y);
						winningIndices.push_back(x);

						if (pieceMatches >= WIN_REQUIREMENT)
						{
							ongoing = false;
							
							if (pieceToCheck == PLAYER_PIECE)
							{
								gameState = STATE_WON;
							}
							else if(pieceToCheck == AI_PIECE)
							{
								gameState = STATE_LOSE;
							}
							std::cout << "HORIZONTAL" << endl;
						}
					}
				}
			}
		}
	}

	// x
	// x
	// x
	void GameState::checkVerticalMatch(int pieceToCheck, vector<int>& winningIndices)
	{
		int pieceMatches = 0;
		bool ongoing = true;

		if (gameState == STATE_PLAYING)
		{
			for (int x = 0; x < GRID_WIDTH && ongoing; x++)
			{
				pieceMatches = 0;
				winningIndices.clear();

				for (int y = 0; y < GRID_HEIGHT && ongoing; y++)
				{
					if (gridArray[(y * GRID_HEIGHT) + x] == pieceToCheck)
					{
						pieceMatches++;
						winningIndices.push_back(y);
						winningIndices.push_back(x);

						if (pieceMatches >= WIN_REQUIREMENT)
						{
							ongoing = false;

							if (pieceToCheck == PLAYER_PIECE)
							{
								gameState = STATE_WON;
							}
							else if (pieceToCheck == AI_PIECE)
							{
								
								gameState = STATE_LOSE;
							}
							std::cout << "VERTICAL" << endl;
						}
					}
				}
			}
		}
	}

	// x
	//  x
	//   x
	void GameState::checkDiagonalDownMatch(int pieceToCheck, vector<int>& winningIndices)
	{
		int pieceMatches = 0;
		bool ongoing = true;

		if (gameState == STATE_PLAYING)
		{
			winningIndices.clear();

			for (int i = 0; i < GRID_HEIGHT && i < GRID_WIDTH && ongoing; i++)
			{
				if (gridArray[(i * GRID_HEIGHT) + i] == pieceToCheck)
				{
					pieceMatches++;
					winningIndices.push_back(i);
					winningIndices.push_back(i);

					if (pieceMatches >= WIN_REQUIREMENT)
					{
						ongoing = false;

						if (pieceToCheck == PLAYER_PIECE)
						{
							gameState = STATE_WON;
						}
						else if (pieceToCheck == AI_PIECE)
						{
							gameState = STATE_LOSE;
						}
						std::cout << "DIAGONAL DOWN" << endl;
					}
				}
			}
		}
	}

	//   x
	//  x
	// x
	void GameState::checkDiagonalUpMatch(int pieceToCheck, vector<int>& winningIndices)
	{
		int pieceMatches = 0;
		bool ongoing = true;
		int y = GRID_HEIGHT - 1, x = 0;

		if (gameState == STATE_PLAYING)
		{
			winningIndices.clear();

			while(y >= 0 && y < GRID_HEIGHT && x >= 0 && x < GRID_WIDTH && ongoing)
			{
				if (gridArray[(y * GRID_HEIGHT) + x] == pieceToCheck)
				{
					pieceMatches++;
					winningIndices.push_back(y);
					winningIndices.push_back(x);

					if (pieceMatches >= WIN_REQUIREMENT)
					{
						ongoing = false;

						if (pieceToCheck == PLAYER_PIECE)
						{
							gameState = STATE_WON;
						}
						else if (pieceToCheck == AI_PIECE)
						{
							gameState = STATE_LOSE;
						}
						std::cout << "DIAGONAL UP" << endl;
					}
				}
				y--;
				x++;
			}
		}
	}

	void GameState::checkDrawMatch()
	{
		bool undetected = true;

		if (gameState == STATE_PLAYING)
		{
			for (int y = 0; y < GRID_HEIGHT && undetected; y++)
			{
				for (int x = 0; x < GRID_WIDTH && undetected; x++)
				{
					if (gridArray[(y * GRID_HEIGHT) + x] == EMPTY_PIECE)
					{
						undetected = false;
					}
				}
			}

			if (undetected)
			{
				gameState = STATE_DRAW;
				std::cout << "DRAW" << endl;
			}
		}
	}
}