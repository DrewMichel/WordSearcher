#ifndef DREW_SEARCH_ORB_H
#define DREW_SEARCH_ORB_H

#include <SFML\Graphics.hpp>
#include "Definitions.h"

namespace Drewski
{
	struct SearchOrb
	{
		public:
			int xBound1, yBound1, xBound2, yBound2;
			int xCap, yCap;
			int xSpeed, ySpeed;
			sf::CircleShape circle;

			bool reversed;

			SearchOrb(int xBound1In = 0, int yBound1In = 0, int xBound2In = 0, int yBound2In = 0, int radiusIn = ORB_RADIUS);

			~SearchOrb();

			sf::CircleShape &getCircle();
	};
}

#endif