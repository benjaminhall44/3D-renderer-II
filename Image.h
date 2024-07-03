#pragma once

#include "Color.h"

class PixelIndexOutOfBounds {};

// Represents a bitmap image
class Image {
public:
	Image(const unsigned int x, const unsigned int y);

	Image(const unsigned int x, const unsigned int y, const Color map[]);

	~Image();

	Color getPixel(unsigned int x, unsigned int y) const;

	void setPixel(unsigned int x, unsigned int y, Color color);

	// Return the images width
	int getSizeX() const;
	// Return the images height
	int getSizeY() const;

	void fill(Color color);


protected:
	const unsigned int x_size;
	const unsigned int y_size;

	Color* contents;

};