#ifndef DREW_INPUT_MANAGER_H
#define DREW_INPUT_MANAGER_H

#include <SFML\Graphics.hpp>

namespace Drewski
{
	class InputManager
	{
		public:
			InputManager() {}
			~InputManager() {}

			bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
			bool isTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow &window);

			sf::Vector2i getMousePosition(sf::RenderWindow &window);


	};
}

#endif