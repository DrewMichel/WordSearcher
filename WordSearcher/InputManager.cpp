#include "InputManager.h"

namespace Drewski
{
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

	bool InputManager::isTextClicked(sf::Text object, sf::Mouse::Button button, sf::RenderWindow &window)
	{
		return (sf::Mouse::isButtonPressed(button) && object.getGlobalBounds().contains((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y));
	}

	sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}
}