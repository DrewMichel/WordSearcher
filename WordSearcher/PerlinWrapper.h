#ifndef DREW_PERLIN_WRAPPER_H
#define DREW_PERLIN_WRAPPER_H

#include "PerlinNoise.h"
#include <SFML\Graphics.hpp>
#include "Definitions.h"

namespace Drewski
{
	struct PerlinWrapper
	{
		int width, height;

		double speed = 0.05;

		sf::Uint8 *pixels;
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		PerlinNoise generator;

		PerlinWrapper(int widthIn = SCREEN_WIDTH, int heightIn = SCREEN_HEIGHT);

		~PerlinWrapper();

		sf::Sprite &getSprite();

		void init(int widthIn = SCREEN_WIDTH, int heightIn = SCREEN_HEIGHT);

		void update();
	};
}

#endif