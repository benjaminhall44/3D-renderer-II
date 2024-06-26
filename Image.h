#pragma once

#include "pixel.h"
#include "TriscelData.h"

class PixelIndexOutOfBounds {};

class Image {
public:
	Image(const unsigned int x, const unsigned int y) : x_size(x), y_size(y) {
		contents = new pixel[x_size * y_size];
	}

	pixel getPixel(unsigned int x, unsigned int y) const {
		if (x < x_size && y < y_size) {
			return contents[x_size * y + x];
		}
		else {
			throw(PixelIndexOutOfBounds());
		}
	}

	void setPixel(unsigned int x, unsigned int y, pixel color) {
		if (x < x_size && y < y_size) {
			contents[x_size * y + x] = color;
		}
		else {
			throw(PixelIndexOutOfBounds());
		}
	}

	int getSizeX() const {
		return x_size;
	}

	int getSizeY() const {
		return y_size;
	}
	void fill(pixel color) {
		for (int x = 0; x < x_size; x++) {
			for (int y = 0; y < y_size; y++) {
				setPixel(x, y, color);
			}
		}
	}


private:
	const unsigned int x_size;
	const unsigned int y_size;

	pixel* contents;

};