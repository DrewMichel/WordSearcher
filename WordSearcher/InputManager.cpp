// IMPORTED PACKAGES
#include "InputManager.h"

// Namespace declaration
namespace Drewski
{
	// Member functions

	// Function that returns true if the object is being clicked
	bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		/*
		if (sf::Mouse::isButtonPressed(button))
		{
			sf::IntRect rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

			if (rect.contains(sf::Mouse::getPosition()))
			{
				return true;
			}
		}

		return false;
		*/

		return (sf::Mouse::isButtonPressed(button) && object.getGlobalBounds().contains((float) sf::Mouse::getPosition(window).x, (float) sf::Mouse::getPosition(window).y));
	}

	// Function that returns true if the object is being clicked
	bool InputManager::isTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		return (sf::Mouse::isButtonPressed(button) && object.getGlobalBounds().contains((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y));
	}

	// Function that returns the position of the mouse as a Vector2i with x and y coordinates
	sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}
}