#ifndef DREW_SEARCH_ORB_H
#define DREW_SEARCH_ORB_H

// IMPORTED PACKAGES:
#include <SFML\Graphics.hpp>
#include "Definitions.h"

// Namespace declaration
namespace Drewski
{
	// Struct that is used to graphically display the search orbs
	struct SearchOrb
	{
		public:
			// Member variables
			int xBound1, yBound1, xBound2, yBound2;
			int distanceCap;
			int xSpeed, ySpeed;
			sf::CircleShape circle;

			bool reversed;

			// Constructor
			SearchOrb(int xBound1In = 0, int yBound1In = 0, int xBound2In = 0, int yBound2In = 0, int radiusIn = ORB_RADIUS);

			// Destructor
			~SearchOrb();

			// Member functions
			sf::CircleShape &getCircle();

			void update();
	};
}

#endif