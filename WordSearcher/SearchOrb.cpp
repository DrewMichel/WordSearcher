#include "SearchOrb.h"

namespace Drewski
{
	SearchOrb::SearchOrb(int xBound1In, int yBound1In, int xBound2In, int yBound2In, int radiusIn) : xBound1(xBound1In), yBound1(yBound1In), xBound2(xBound2In), yBound2(yBound2In), reversed(false)
	{
		sf::Color color((rand() % 1) + 120, (rand() % 100) + 120, (rand() % 100) + 120, 255);
		//sf::Image image;
		//sf::Texture texture;
		//image.create(radiusIn * 2, radiusIn * 2, color);
		//texture.create(radiusIn * 2, radiusIn * 2);
		//texture.loadFromImage(image);
		
		circle.setFillColor(color);
		//circle.setOutlineColor(color);
		circle.setRadius(radiusIn);
		circle.setPosition(xBound1, yBound1);
	}

	SearchOrb::~SearchOrb()
	{

	}

	sf::CircleShape &SearchOrb::getCircle()
	{
		return circle;
	}


}

