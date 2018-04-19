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
}