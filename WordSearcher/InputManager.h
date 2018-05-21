#ifndef DREW_INPUT_MANAGER_H
#define DREW_INPUT_MANAGER_H

// IMPORTED PACKAGES:
#include <SFML\Graphics.hpp>

// Namespace declaration
namespace Drewski
{
	class InputManager
	{
		public:
			// Constructor
			InputManager() {}

			// Destructor
			~InputManager() {}

			// Member functions
			bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);
			bool isTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow &window);

			sf::Vector2i getMousePosition(sf::RenderWindow &window);
	};
}

#endif