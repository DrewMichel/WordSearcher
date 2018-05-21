// IMPORTED PACKAGES:
#include "GameState.h"
#include <sstream>
#include <iostream>
#include "PauseState.h"
#include "GameOverState.h"
#include <chrono>
#include <algorithm>

// Namespace declaration
namespace Drewski
{
	// Function prototype
	bool operator<(const sf::Text& one, const sf::Text& two);

	// Constructor
	GameState::GameState(GameDataRef dataIn) : data(dataIn)
	{

	}

	// Destructor
	GameState::~GameState()
	{

	}

	// Function responsible for initializing the state
	void GameState::init()
	{
		//gameState = STATE_PLAYING;

		// Loads font
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

		// Generates graphical grid words and adds them to grid text unordered_map
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

		// Iterates over the original search unordered_map and creates and stores Text objects into search text vector
		for (auto iterator = data->originalSearch.begin(); iterator != data->originalSearch.end(); iterator++)
		{
			sf::Text text;
			text.setFont(this->data->assetManager.getFont("courier new bold"));
			text.setString(iterator->second.getOriginal());
			text.setFillColor(sf::Color(255, 215, 0, 255));
			text.setCharacterSize(20);

			//text.setPosition(text.getPosition().x + (25 * 2) + (SCREEN_WIDTH / 2), text.getPosition().y + 25 + (index * 20));

			this->data->assetManager.addSearchText(text);
			index++;
		}

		// Sorts the search text vector using global operator < overload
		sort(data->assetManager.getSearchTextVector().begin(), data->assetManager.getSearchTextVector().end(), operator<);

		index = 0;
		int index2 = 0;

		// Iterates over the sorted search text vector and assigns x and y positions to each search word based on position in vector
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

		// Prints the number of original search words to console
		cout << "ORIGINAL SEARCH SIZE: " << data->originalSearch.size() << endl;

		// TODO: SEARCH FOR AND FILL SEARCHWORD COORDINATES

		// TODO: GENERATE ORBS IN MAP/UNORDERED_MAP HERE

		// TODO: MOVE ORBS BETWEEN THEIR COORDINATES IN UPDATE FUNCTION

		// TODO: IF SEARCHWORD IS OUTLINING, DISPLAY ORBS IN DRAW


		//pauseButton.setTexture(this->data->assetManager.getTexture("Pause Button"));
		//pauseButton.setPosition(this->data->window.getSize().x - pauseButton.getLocalBounds().width, pauseButton.getPosition().y);
		//pauseButton.setColor(sf::Color(0, 0, 0, 255));

		// Solves the grid by scanning it for search targets
		solve();
	}

	// Function responsible for handling input on state
	void GameState::handleInput()
	{
		// Event variable used to capture events
		sf::Event sfEvent;

		// Loops while the event has unprocessed events
		while (this->data->window.pollEvent(sfEvent))
		{
			// Closes the window if the event is of the correct type
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

			// Iterates through the search text vector and determines if any of the search words are being clicked
			for (auto iterator = data->assetManager.getSearchTextVector().begin(); iterator != data->assetManager.getSearchTextVector().end(); iterator++)
			{
				// If the current search word is clicked
				if (data->inputManager.isTextClicked(*iterator, sf::Mouse::Left, this->data->window))
				{
					// Get the string from the text object
					string name = iterator->getString();

					// Use the name to index into unordered_map and flip its selected state
					data->originalSearch[name].flipOutlining();
					
					// Change color to yellow if unselected or cyan if selected
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
			/*
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
			*/
		}
	}

	// Function responsible for updating the state
	void GameState::update(float deltaTimeIn)
	{
		// Iterates over the search orb map and calls update on each orb
		for (auto iterator = data->assetManager.getOrbMap().begin(); iterator != data->assetManager.getOrbMap().end(); iterator++)
		{
			iterator->second.update();
		}
	}

	// Function responsible for drawing the state
	void GameState::draw(float deltaTimeIn)
	{
		// Clears the window and sets all pixels to black
		this->data->window.clear(sf::Color::Black);
		//this->data->window.clear();

		//this->data->assetManager.getPerlin().update();

		//this->data->window.draw(this->data->assetManager.getPerlin().getSprite());
		
		//this->data->window.draw(this->background);

		// Declares variables
		sf::Image centerImage;
		sf::Sprite centerSprite;
		sf::Texture centerTexture;

		// Creates and image, a texture, and a sprite to draw background
		centerImage.create(30, SCREEN_HEIGHT, sf::Color(255, 255, 255, 255));

		centerTexture.create(30, SCREEN_HEIGHT);
		centerTexture.loadFromImage(centerImage);

		centerSprite.setTexture(centerTexture);

		centerSprite.setPosition(SCREEN_WIDTH / 2, centerSprite.getPosition().y);

		// Draws background sprite
		this->data->window.draw(centerSprite);

		//this->data->window.draw(this->pauseButton);

		/*
		for (auto iterator = this->data->assetManager.getOrbMap().begin(); iterator != this->data->assetManager.getOrbMap().end(); iterator++)
		{
			this->data->window.draw(iterator->second.getCircle());
		}
		*/

		// Iterates over the search text vector to display each element
		for (auto iterator = this->data->assetManager.getSearchTextVector().begin(); iterator != this->data->assetManager.getSearchTextVector().end(); iterator++)
		{
			// Gets the string from text object
			string name = iterator->getString();

			// HANDLE ORB DRAWING
			// Place orbs into unordered_map<string (RAW), Orb> with x1, y1, x2, y2 from SearchWord
			if (this->data->originalSearch[name].getOutlining())
			{
				this->data->window.draw(this->data->assetManager.getOrb(name).getCircle());
			}

			// Draws the text object
			this->data->window.draw(*iterator);
		}

		// Iterates over the grid map and draws each element
		for (auto iterator = this->data->assetManager.getGridTextMap().begin(); iterator != this->data->assetManager.getGridTextMap().end(); iterator++)
		{
			this->data->window.draw(iterator->second);
		}

		// Updates or displays the window
		this->data->window.display();
	}

	// Function that solves the grid by invoking other functions
	void GameState::solve()
	{
		scanHorizontally();
		scanVertically();
		scanDiagonallyDown();
		scanDiagonallyUp();
	}

	// x x x

	// Function that horizontally scans the grid for search targets
	void GameState::scanHorizontally()
	{
		string current;

		// Iterates over the grid's height
		for (int y = 0; y < data->grid.size(); y++)
		{
			// Iterates over the grid's width
			for (int x = 0; x < data->grid[y].size(); x++)
			{
				current.clear();
				
				// Iterates from current width (x) index to the end of the width
				for (int end = x; end < data->grid[y].size(); end++)
				{
					// Appends character into string
					current.push_back(data->grid[y][end]);

					// Checks to see if the unordered_map contains the current string
					if (data->parseSearch.count(current) > 0)
					{
						//data->originalSearch[data->parseSearch[current]];

						// Adds a search orb to unordered_map
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

	// Function that vertically scans the grid for search targets
	void GameState::scanVertically()
	{
		string current;

		// Iterates over the grid's height
		for (int y = 0; y < data->grid.size(); y++)
		{
			// Iterates over the grid's width
			for (int x = 0; x < data->grid[y].size(); x++)
			{
				current.clear();

				// Iterates from current height (y) index to the end of the height
				for (int end = y; end < data->grid.size(); end++)
				{
					// Appends character into string
					current.push_back(data->grid[end][x]);

					// Checks to see if the unordered_map contains the string
					if (data->parseSearch.count(current) > 0)
					{
						// Adds a search orb into unordered_map
						data->assetManager.addOrb(data->parseSearch[current], SearchOrb(x, y, x, end));
					}
				}
			}
		}
	}

	// x
	//  x
	//   x

	// Function that scans diagonally down by call other functions
	void GameState::scanDiagonallyDown()
	{
		// Scans top and bottom halves
		scanDiagonallyDownTop();
		scanDiagonallyDownBottom();
	}

	// axx
	//  bx
	//   c

	// Function that diagonally scans down the top half of the grid for search targets
	void GameState::scanDiagonallyDownTop()
	{
		string current;
		
		// Checks to see if the grid has elements
		if (data->grid.size() > 0)
		{
			// scan top of screen ( x, y, end)

			// Iterates over the width of the grid
			for (int x = 0; x < data->grid[0].size(); x++)
			{
				// Iterates over the height of the grid
				for (int y = 0; y < data->grid.size(); y++)
				{
					current.clear();
					
					// Iterates from current height (y) index to end of either width or height
					for (int end = y; end < data->grid.size() && end + x < data->grid[y].size(); end++)
					{
						// Pushes character onto string
						current.push_back(data->grid[end][x + end]);

						// Checks to see if the unordered_map contains the string
						if (data->parseSearch.count(current) > 0)
						{
							// Adds a search orb to the unordered_map
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

	// Function that diagonally scans down the bottom of the grid for search targets
	void GameState::scanDiagonallyDownBottom()
	{
		string current;

		// scan bottom of screen ( y, x, end)

		// 0 checked by top

		// Checks to seee if the grid contains elementts
		if (data->grid.size() > 0)
		{
			// Iterates over the height of the grid starting at 1
			for (int y = 1; y < data->grid.size(); y++)
			{
				// Iterates diagonally within height and width
				for (int offset = 0; offset + y < data->grid.size() && offset < data->grid[y].size(); offset++)
				{
					current.clear();
					
					// Iterates diagonally from offset index to end of width and height
					for (int end = offset; end + y < data->grid.size() && end < data->grid[y].size(); end++)
					{
						// Appends character onto string
						current.push_back(data->grid[y + end][end]);

						// Checks to see if the unordered_map contains the string
						if (data->parseSearch.count(current) > 0)
						{
							// Adds a search orb into the unordered_map
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
	
	// Function that diagonally up by calling other functions
	void GameState::scanDiagonallyUp()
	{
		// Scans top and bottom halves
		scanDiagonallyUpTop();
		scanDiagonallyUpBottom();
	}

	// xxx
	// xxo
	// xoo

	// Function that diagonally scans up the top of the grid for search targets
	void GameState::scanDiagonallyUpTop()
	{
		string current;

		// Checks to see if the grid contains elements
		if (data->grid.size() > 0)
		{
			// Iterates over the height of the grid
			for (int y = 0; y < data->grid.size(); y++)
			{
				// Iterates diagonally from height (y) index to 0
				for (int offset = y; y - offset >= 0 && offset < data->grid[y].size(); offset--)
				{
					current.clear();

					// Iterates diagonally from offset index to 0
					for (int end = offset; y - end >= 0 && end < data->grid[y].size(); end--)
					{
						// Appends the character to string
						current.push_back(data->grid[y - end][end]);

						// Checks to see if the unordered_map contains the string
						if (data->parseSearch.count(current) > 0)
						{
							// Adds search orb to unordered_map
							data->assetManager.addOrb(data->parseSearch[current], SearchOrb(offset, y - offset, end, y - end));
						}
					}
				}
			}
		}
	}

	// ooo
	// oox
	// oxx

	// Function that diagonally scans up the bottom of the grid for search targets
	void GameState::scanDiagonallyUpBottom()
	{
		string current;

		// Checks to see if the grid contains elements
		if (data->grid.size() > 0)
		{
			// Iterates over the width of the grid starting at 1
			for (int x = 1; x < data->grid[0].size(); x++)
			{
				// Iterates diagonally from 0 within width and height
				for (int offset = 0; data->grid.size() - offset >= 0 && offset + x < data->grid[data->grid.size() - 1 - offset].size(); offset++)
				{
					current.clear();

					// Iterates diagonally from offset index to width and height
					for (int end = offset; data->grid.size() - end >= 0 && end + x < data->grid[data->grid.size() - 1 - end].size(); end++)
					{
						// Appends the character onto the string
						current.push_back(data->grid[data->grid.size() - end - 1][x + end]);

						// Checks to see if the unordered_map contains the string
						if (data->parseSearch.count(current) > 0)
						{
							// Adds a search orb to the unordered_map
							data->assetManager.addOrb(data->parseSearch[current], SearchOrb(x + offset, data->grid.size() - 1 - offset, x + end, data->grid.size() - 1 - end));
						}
					}
				}
			}
		}
	}

	// Global sf::Text operator function for <
	// Function that is used to compare two text objects based on their strings
	bool operator<(const sf::Text& one, const sf::Text& two)
	{
		string curOne = WordSanitizer::removeWhitespace(one.getString());
		string curTwo = WordSanitizer::removeWhitespace(two.getString());

		return curOne < curTwo;
	}
}