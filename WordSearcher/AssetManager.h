#ifndef DREW_ASSET_MANAGER_H
#define DREW_ASSET_MANAGER_H

// IMPORTED PACKAGES:
#include <string>
#include <unordered_map>
#include <SFML\Graphics.hpp>
#include "PerlinWrapper.h"
#include <vector>
#include "SearchOrb.h"

// Namespace usage which allows the direct use of declarations
using namespace std;

// Namespace declaration
namespace Drewski
{
	// Class that manages the loading and using of assets such as fonts and textures
	class AssetManager
	{
		private:
			// Member variables
			unordered_map<string, sf::Texture> textureMap;
			unordered_map<string, sf::Font> fontMap;
			unordered_map<string, sf::Text> gridTextMap;
			vector<sf::Text> searchTextVector;
			unordered_map<string, SearchOrb> orbMap;
		public:
			// Constructors
			AssetManager() {}
			~AssetManager() {}

			// Member functions
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

			void addOrb(string name, SearchOrb orb);

			SearchOrb &getOrb(string name);

			unordered_map<string, SearchOrb> &getOrbMap();

		
			//PerlinWrapper perlin;
	};
}

#endif