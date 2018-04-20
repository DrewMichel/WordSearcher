#include "PerlinWrapper.h"

namespace Drewski
{
	PerlinWrapper::PerlinWrapper(int widthIn, int heightIn)
	{
		width = widthIn;
		height = heightIn;
	}

	PerlinWrapper::~PerlinWrapper()
	{
		delete[] pixels;
	}

	sf::Sprite &PerlinWrapper::getSprite()
	{
		return sprite;
	}

	void PerlinWrapper::init(int widthIn, int heightIn)
	{
		generator;

		pixels = new sf::Uint8[width * height * 4];

		double z = 0.5f;
		int number;
		int random = rand();

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				number = 4 * ((y * SCREEN_WIDTH) + x);
				pixels[number] = generator.noise(x * speed, y * speed, z) * 255; // RED
				pixels[number + 1] = generator.noise(x * speed + random, y * speed + random, z) * 255; // GREEN
				pixels[number + 2] = generator.noise(x * speed + random * random, y * speed + random * random, z) * 255; // BLUE
				pixels[number + 3] = 255; // ALPHA
			}
		}

		image.create(width, height, pixels);
		texture.create(width, height);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}

	void PerlinWrapper::update()
	{
		double z = 0.5f;
		int number;
		int random = rand();

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				number = 4 * ((y * SCREEN_WIDTH) + x);
				pixels[number] = generator.noise(x * speed, y * speed, z) * 255; // RED
				pixels[number + 1] = generator.noise(x * speed + random, y * speed + random, z) * 255; // GREEN
				pixels[number + 2] = generator.noise(x * speed + random * random, y * speed + random * random, z) * 255; // BLUE
				pixels[number + 3] = 255; // ALPHA
			}
		}

		image.create(width, height, pixels);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
}
