#ifndef DREW_ASSET_MANAGER_H
#define DREW_ASSET_MANAGER_H

#include <string>
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include "PerlinWrapper.h"
#include <vector>

using namespace std;

namespace Drewski
{
	class AssetManager
	{
		public:
			AssetManager() {}
			~AssetManager() {}

			void loadTexture(string name, string file);
			sf::Texture &getTexture(string name);

			void loadFont(string name, string file);
			sf::Font &getFont(string name);

			void addGridText(string name, sf::Text text);
			sf::Text &getGridText(string name);

			unordered_map<string, sf::Text> &getGridTextMap();

			void addSearchText(sf::Text text);
			sf::Text &getSearchText(int index);

			vector<sf::Text> &getSearchTextVector();
			//PerlinWrapper &getPerlin();

		private:
			unordered_map<string, sf::Texture> textureMap;
			unordered_map<string, sf::Font> fontMap;
			unordered_map<string, sf::Text> gridTextMap;
			vector<sf::Text> searchTextVector;

			//PerlinWrapper perlin;
	};
}

#endif