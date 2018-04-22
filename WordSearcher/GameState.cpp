#include "GameState.h"

#include <sstream>
#include <iostream>
#include "PauseState.h"
#include "GameOverState.h"
#include "PerlinNoise.h"
#include <chrono>
#include <algorithm>

namespace Drewski
{
	// Global sf::Text operator function for <
	bool operator<(const sf::Text& one, const sf::Text& two);

	// Constructor
	GameState::GameState(GameDataRef dataIn) : data(dataIn)
	{

	}

	GameState::~GameState()
	{

	}

	/*
	int compareSFText(const sf::Text& one, const sf::Text& two)
	{
		string curOne = one.getString();
		string curTwo = two.getString();

		if (curOne > curTwo)
		{
			return 1;
		}
		else if (curOne < curTwo)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
	*/

	

	void GameState::init()
	{
		//gameState = STATE_PLAYING;

		this->data->assetManager.loadFont("courier new bold", FONT_COURIER_NEW_BOLD_FILEPATH);
		//this->data->assetManager.loadTexture("Pause Button", PAUSE_BUTTON);
		/*
		sf::Text text;
		text.setFont(this->data->assetManager.getFont("arial"));
		text.setString("SAMPLE TEXT");
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(24);

		this->data->assetManager.addGridText("TEST", text);
		*/

		for(int i = 0; i < data->grid.size(); i++)
		{
			sf::Text text;
			text.setFont(this->data->assetManager.getFont("courier new bold"));
			text.setString(WordSanitizer::smudge(data->grid[i]));
			text.setFillColor(sf::Color(255, 215, 0, 255));
			text.setCharacterSize(25);

			text.setPosition(text.getPosition().x + 25, text.getPosition().y +  25 + (i * 30));

			this->data->assetManager.addGridText("GRID" + to_string(i), text);
		}

		int index = 0;

		for (auto iterator = data->originalSearch.begin(); iterator != data->originalSearch.end(); iterator++)
		{
			sf::Text text;
			text.setFont(this->data->assetManager.getFont("courier new bold"));
			text.setString(iterator->second.getOriginal());
			text.setFillColor(sf::Color(255, 215, 0, 255));
			text.setCharacterSize(20);

			//text.setPosition(text.getPosition().x + (25 * 2) + (SCREEN_WIDTH / 2), text.getPosition().y + 25 + (index * 20));

			this->data->assetManager.addSearchText( text);
			index++;
		}

		sort(data->assetManager.getSearchTextVector().begin(), data->assetManager.getSearchTextVector().end(), operator<);

		index = 0;

		for (auto iterator = data->assetManager.getSearchTextVector().begin(); iterator != data->assetManager.getSearchTextVector().end(); iterator++)
		{
			iterator->setPosition(iterator->getPosition().x + (25 * 2) + (SCREEN_WIDTH / 2), iterator->getPosition().y + 25 + (index * 20));
			index++;
		}

		//data->assetManager.addOrb("ADAMS", SearchOrb(200, 200, 200, 200, 200));

		cout << "ORIGINAL SEARCH SIZE: " << data->originalSearch.size() << endl;

		// TODO: SEARCH FOR AND FILL SEARCHWORD COORDINATES

		// TODO: GENERATE ORBS IN MAP/UNORDERED_MAP HERE

		// TODO: MOVE ORBS BETWEEN THEIR COORDINATES IN UPDATE FUNCTION

		// TODO: IF SEARCHWORD IS OUTLINING, DISPLAY ORBS IN DRAW


		//pauseButton.setTexture(this->data->assetManager.getTexture("Pause Button"));
		//pauseButton.setPosition(this->data->window.getSize().x - pauseButton.getLocalBounds().width, pauseButton.getPosition().y);
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
			for (auto iterator = data->assetManager.getSearchTextVector().begin(); iterator != data->assetManager.getSearchTextVector().end(); iterator++)
			{
				if (data->inputManager.isTextClicked(*iterator, sf::Mouse::Left, this->data->window))
				{
					string name = iterator->getString();

					data->originalSearch[name].flipOutlining();
					
					if (data->originalSearch[name].getOutlining())
					{
						iterator->setFillColor(sf::Color(0, 255, 255, 255));
					}
					else
					{
						iterator->setFillColor(sf::Color(255, 215, 0, 255));
					}
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

		//this->data->window.draw(this->pauseButton);

		/*
		for (auto iterator = this->data->assetManager.getOrbMap().begin(); iterator != this->data->assetManager.getOrbMap().end(); iterator++)
		{
			this->data->window.draw(iterator->second.getCircle());
		}
		*/

		for (auto iterator = this->data->assetManager.getSearchTextVector().begin(); iterator != this->data->assetManager.getSearchTextVector().end(); iterator++)
		{
			string name = iterator->getString();

			// HANDLE ORB DRAWING
			// Place orbs into unordered_map<string (RAW), Orb> with x1, y1, x2, y2 from SearchWord
			if (this->data->originalSearch[name].getOutlining())
			{
				this->data->window.draw(this->data->assetManager.getOrb(name).getCircle());
			}

			this->data->window.draw(*iterator);
		}

		for (auto iterator = this->data->assetManager.getGridTextMap().begin(); iterator != this->data->assetManager.getGridTextMap().end(); iterator++)
		{
			this->data->window.draw(iterator->second);
		}

		

		this->data->window.display();
	}

	bool operator<(const sf::Text& one, const sf::Text& two)
	{
		string curOne = one.getString();
		string curTwo = two.getString();

		//cout << "COMPARING: " << curOne << " < " << curTwo << " == " << (curOne < curTwo) << endl;

		return curOne < curTwo;
	}
}