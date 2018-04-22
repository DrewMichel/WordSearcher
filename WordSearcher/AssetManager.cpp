#include "AssetManager.h"

namespace Drewski
{
	void AssetManager::loadTexture(string name, string file)
	{
		sf::Texture tex;

		if (tex.loadFromFile(file))
		{
			this->textureMap[name] = tex;
		}
	}

	sf::Texture &AssetManager::getTexture(string name)
	{
		return this->textureMap.at(name);
	}


	void AssetManager::loadFont(string name, string file)
	{
		sf::Font font;

		if (font.loadFromFile(file))
		{
			this->fontMap[name] = font;
		}
	}

	sf::Font &AssetManager::getFont(string name)
	{
		return this->fontMap.at(name);
	}

	sf::Text &AssetManager::getGridText(string name)
	{
		return this->gridTextMap.at(name);
	}

	void AssetManager::addGridText(string name, sf::Text text)
	{
		this->gridTextMap[name] = text;
	}

	unordered_map<string, sf::Text> &AssetManager::getGridTextMap()
	{
		return this->gridTextMap;
	}

	void AssetManager::addSearchText(sf::Text text)
	{
		searchTextVector.push_back(text);
	}

	sf::Text &AssetManager::getSearchText(int index)
	{
		return searchTextVector.at(index);
	}

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

	void AssetManager::addOrb(string name, SearchOrb orb)
	{
		orbMap[name] = orb;
	}

	SearchOrb &AssetManager::getOrb(string name)
	{
		return orbMap[name];
	}

	unordered_map<string, SearchOrb> &AssetManager::getOrbMap()
	{
		return orbMap;
	}
}