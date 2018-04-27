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
			//text.setCharacterSize(350 / data->grid[i].size() + 1);
			//cout << "CHARACTER SIZE: " << text.getCharacterSize() << endl;
			text.setCharacterSize(18);

			text.setPosition(text.getPosition().x + 25, text.getPosition().y + 25 + (i * 30));

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
		int index2 = 0;

		for (auto iterator = data->assetManager.getSearchTextVector().begin(); iterator != data->assetManager.getSearchTextVector().end(); iterator++)
		{
			if (25 + (index * 20) >= SCREEN_HEIGHT - 100)
			{

				iterator->setPosition(iterator->getPosition().x + (25 * 2) + (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 4), iterator->getPosition().y + 25 + (index2 * 20));
				index2++;
			}
			else
			{
				iterator->setPosition(iterator->getPosition().x + (25 * 2) + (SCREEN_WIDTH / 2), iterator->getPosition().y + 25 + (index * 20));
			}

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

		solve();
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
		for (auto iterator = data->assetManager.getOrbMap().begin(); iterator != data->assetManager.getOrbMap().end(); iterator++)
		{
			iterator->second.update();
		}
	}

	void GameState::draw(float deltaTimeIn)
	{
		this->data->window.clear(sf::Color::Black);
		//this->data->window.clear();

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

	void GameState::solve()
	{
		scanHorizontally();
		scanVertically();
		scanDiagonallyDown();
		scanDiagonallyUp();
	}

	// x x x
	void GameState::scanHorizontally()
	{
		string current;

		for (int y = 0; y < data->grid.size(); y++)
		{
			for (int x = 0; x < data->grid[y].size(); x++)
			{
				current.clear();
				for (int end = x; end < data->grid[y].size(); end++)
				{
					current.push_back(data->grid[y][end]);

					if (data->parseSearch.count(current) > 0)
					{
						//data->originalSearch[data->parseSearch[current]];

						data->assetManager.addOrb(data->parseSearch[current], SearchOrb(x, y, end, y));

						// erase and erase reverse (unnecessary?)
					}
				}
			}
		}
	}

	// x
	// x
	// x
	void GameState::scanVertically()
	{
		string current;

		for (int y = 0; y < data->grid.size(); y++)
		{
			for (int x = 0; x < data->grid[y].size(); x++)
			{
				current.clear();
				for (int end = y; end < data->grid.size(); end++)
				{
					current.push_back(data->grid[end][x]);

					if (data->parseSearch.count(current) > 0)
					{
						data->assetManager.addOrb(data->parseSearch[current], SearchOrb(x, y, x, end));
					}
				}
			}
		}
	}

	// x
	//  x
	//   x
	void GameState::scanDiagonallyDown()
	{
		scanDiagonallyDownTop();
		scanDiagonallyDownBottom();

		// scan bottom
	}

	// axx
	//  bx
	//   c
	void GameState::scanDiagonallyDownTop()
	{
		string current;
		
		if (data->grid.size() > 0)
		{
			// scan top of screen ( x, y, end)
			for (int x = 0; x < data->grid[0].size(); x++)
			{
				for (int y = 0; y < data->grid.size(); y++)
				{
					current.clear();
					// for(int end = y + 1
					for (int end = y; end < data->grid.size() && end + x < data->grid[y].size(); end++)
					{
						current.push_back(data->grid[end][x + end]);

						if (data->parseSearch.count(current) > 0)
						{
							data->assetManager.addOrb(data->parseSearch[current], SearchOrb(x + y, y, x + end, end));
						}
					}
				}
			}
		}
	}

	// ooo
	// aoo
	// xbo
	void GameState::scanDiagonallyDownBottom()
	{
		string current;

		// scan bottom of screen ( y, x, end)

		// 0 checked by top
		if (data->grid.size() > 0)
		{
			for (int y = 1; y < data->grid.size(); y++)
			{
				for (int offset = 0; offset + y < data->grid.size() && offset < data->grid[y].size(); offset++)
				{
					current.clear();
					// for(int end = offset + 1
					for (int end = offset; end + y < data->grid.size() && end < data->grid[y].size(); end++)
					{
						current.push_back(data->grid[y + end][end]);

						if (data->parseSearch.count(current) > 0)
						{
							data->assetManager.addOrb(data->parseSearch[current], SearchOrb(offset, offset + y, end, y + end));
						}
					}
				}
			}
		}
	}



	//   x
	//  x
	// x
	void GameState::scanDiagonallyUp()
	{
		scanDiagonallyUpTop();
		scanDiagonallyUpBottom();
	}

	void GameState::scanDiagonallyUpTop()
	{
		string current;

		if (data->grid.size() > 0)
		{
			// scan top of screen
			for (int y = 0; y < data->grid.size(); y++)
			{
				for (int offset = y; y - offset >= 0 && offset < data->grid[y].size(); offset--)
				{
					current.clear();
					for (int end = offset; y - end >= 0 && end < data->grid[y].size(); end--)
					{
						current.push_back(data->grid[y - end][end]);

						if (data->parseSearch.count(current) > 0)
						{
							data->assetManager.addOrb(data->parseSearch[current], SearchOrb(offset, y - offset, end, y - end));
						}
					}
				}
			}
		}
		
	}

	void GameState::scanDiagonallyUpBottom()
	{
		string current;

		
		// scan bottom of screen
		if (data->grid.size() > 0)
		{
			for (int x = 1; x < data->grid[0].size(); x++)
			{
				for (int offset = 0; data->grid.size() - offset >= 0 && offset + x < data->grid[data->grid.size() - 1 - offset].size(); offset++)
				{
					current.clear();
					for (int end = offset; data->grid.size() - end >= 0 && end + x < data->grid[data->grid.size() - 1 - end].size(); end++)
					{
						current.push_back(data->grid[data->grid.size() - end - 1][x + end]);

						if (data->parseSearch.count(current) > 0)
						{
							data->assetManager.addOrb(data->parseSearch[current], SearchOrb(x + offset, data->grid.size() - 1 - offset, x + end, data->grid.size() - 1 - end));
						}
					}
				}
			}
		}
		
	}

	bool operator<(const sf::Text& one, const sf::Text& two)
	{
		string curOne = WordSanitizer::removeWhitespace(one.getString());
		string curTwo = WordSanitizer::removeWhitespace(two.getString());

		return curOne < curTwo;
	}
}