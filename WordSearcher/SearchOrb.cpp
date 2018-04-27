#include "SearchOrb.h"
#include <iostream>
#include <assert.h>

namespace Drewski
{
	SearchOrb::SearchOrb(int xBound1In, int yBound1In, int xBound2In, int yBound2In, int radiusIn) : xBound1(30 + (xBound1In * 22) ), yBound1(yBound1In * 30 + 34), xBound2(30 + (xBound2In * 22)), yBound2(yBound2In * 30 + 34), reversed(false)
	{
		reversed = false;
		distanceCap = ORB_DISTANCE_CAP;
		sf::Color color((rand() % 100) + 100, (rand() % 100) + 100, (rand() % 100) + 100, 255);
		//sf::Image image;
		//sf::Texture texture;
		//image.create(radiusIn * 2, radiusIn * 2, color);
		//texture.create(radiusIn * 2, radiusIn * 2);
		//texture.loadFromImage(image);

		circle.setFillColor(color);
		//circle.setOutlineColor(color);
		circle.setRadius(radiusIn);

		circle.setOrigin(circle.getRadius(), circle.getRadius());

		//xBound1 += radiusIn / 2;
		//xBound2 += radiusIn / 2;

		//circle.setPosition(xBound1, yBound1);
		//circle.setPosition(xBound2 * 18 + 75, yBound2 * 30 + 20);

		//circle.setPosition(12 + (7 * 22), yBound1);
		circle.setPosition(xBound1, yBound1);
	}

	SearchOrb::~SearchOrb()
	{

	}

	sf::CircleShape &SearchOrb::getCircle()
	{
		return circle;
	}

	void SearchOrb::update()
	{
		int x = circle.getPosition().x;
		int y = circle.getPosition().y;

		double distance;
		double theta;

		// reversed target x1, y1
		if (reversed == true)
		{
			distance = hypot(xBound1 - x, yBound1 - y);
			theta = atan2(yBound1 - y, xBound1 - x);
		}
		else // target x2, y2
		{
			distance = hypot(xBound2 - x, yBound2 - y);
			theta = atan2(yBound2 - y, xBound2 - x);
		}

		if (distance > distanceCap)
		{
			//circle.setPosition(cosf(theta) * distanceCap, sinf(theta) * distanceCap);
			circle.move(cos(theta) * distanceCap, sin(theta) * distanceCap );
		}
		else
		{
			reversed = !reversed;
			//std::cout << "DISTANCE: " << distance << std::endl;

			//circle.setPosition(cosf(theta) * distance, sinf(theta) * distance);
			circle.move(cos(theta) * distance, sin(theta) * distance );
		}
	}
}

