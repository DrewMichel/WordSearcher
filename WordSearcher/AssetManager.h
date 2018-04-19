#ifndef DREW_ASSET_MANAGER_H
#define DREW_ASSET_MANAGER_H

#include <string>
#include <unordered_map>
#include <SFML\Graphics.hpp>

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

		private:
			unordered_map<string, sf::Texture> textureMap;
			unordered_map<string, sf::Font> fontMap;
	};
}

#endif