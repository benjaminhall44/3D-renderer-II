#pragma once
#include "Image.h"
#include "SFML/Graphics.hpp"

class FailedToConstruct {};

class SpriteImage : public Image {
public:
	SpriteImage(const unsigned int x, const unsigned int y) : Image(x, y),texture() {
		if (!texture.create(x_size, y_size)) {
			throw FailedToConstruct();
		}
		pixels = new sf::Uint8[x_size * y_size * 4];
	};

	sf::Sprite getSprite() {
		for (int i = 0; i < x_size * y_size; i++) {
			pixels[i * 4 + 0] = contents[i].red;
			pixels[i * 4 + 1] = contents[i].green;
			pixels[i * 4 + 2] = contents[i].blue;
			pixels[i * 4 + 3] = 255;
		}
		texture.update(pixels);

		return sf::Sprite(texture);
	}
private:
	sf::Texture texture;
	sf::Uint8* pixels;
};