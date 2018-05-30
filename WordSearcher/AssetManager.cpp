// Created by: Andrew Steven Michel
// Date Created: May 2018

// IMPORTED PACKAGES:
#include "AssetManager.h"

// Namespace declaration
namespace Drewski
{
	// Member functions

	// Function that loads a texture from file and stores it into
	// texture map with the given name
	void AssetManager::loadTexture(string name, string file)
	{
		sf::Texture tex;

		if (tex.loadFromFile(file))
		{
			this->textureMap[name] = tex;
		}
	}

	// Function that returns a texture with the given name by reference
	sf::Texture &AssetManager::getTexture(string name)
	{
		return this->textureMap.at(name);
	}

	// Function that loads a font from file and stores it into
	// font map with the given name
	void AssetManager::loadFont(string name, string file)
	{
		sf::Font font;

		if (font.loadFromFile(file))
		{
			this->fontMap[name] = font;
		}
	}

	// Function that returns a font with the given name by reference
	sf::Font &AssetManager::getFont(string name)
	{
		return this->fontMap.at(name);
	}

	// Function that returns a text with the given name by reference
	sf::Text &AssetManager::getGridText(string name)
	{
		return this->gridTextMap.at(name);
	}

	// Function that stores a text with the given name
	void AssetManager::addGridText(string name, sf::Text text)
	{
		this->gridTextMap[name] = text;
	}

	// Function that returns the grid text map by reference
	unordered_map<string, sf::Text> &AssetManager::getGridTextMap()
	{
		return this->gridTextMap;
	}

	// Function that adds a text to the vector
	void AssetManager::addSearchText(sf::Text text)
	{
		searchTextVector.push_back(text);
	}

	// Function that returns a text from vector at the given index
	sf::Text &AssetManager::getSearchText(int index)
	{
		return searchTextVector.at(index);
	}

	// Function that returns the search text vector by reference
	vector<sf::Text> &AssetManager::getSearchTextVector()
	{
		return searchTextVector;
	}

	/*
	PerlinWrapper &AssetManager::getPerlin()
	{
		return perlin;
	}
	*/

	// Function that adds a search orb to orb map with the given name
	void AssetManager::addOrb(string name, SearchOrb orb)
	{
		orbMap[name] = orb;
	}

	// Function that returns a search orb with the given name
	SearchOrb &AssetManager::getOrb(string name)
	{
		return orbMap[name];
	}

	// Function that returns the orb map by reference
	unordered_map<string, SearchOrb> &AssetManager::getOrbMap()
	{
		return orbMap;
	}
}