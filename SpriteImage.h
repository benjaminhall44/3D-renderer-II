#pragma once
#include "Image.h"
#include "SFML/Graphics.hpp"

// Thrown when texture::create(x,y) fails in the SpriteImage constructor
class FailedToConstruct {};

// An Image which can convert itself into a Sprite object used
// by SFML graphics using the function
// getSprite()
class SpriteImage : public Image {
public:
	SpriteImage(const unsigned int x, const unsigned int y);
	sf::Sprite getSprite();
private:
	sf::Texture texture;
	sf::Uint8* pixels;
};