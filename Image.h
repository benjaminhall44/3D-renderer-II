#pragma once

#include "Color.h"
#include "TriscelData.h"

class PixelIndexOutOfBounds {};

class Image {
public:
	Image(const unsigned int x, const unsigned int y) : x_size(x), y_size(y) {
		contents = new Color[x_size * y_size];
	}

	Image(const unsigned int x, const unsigned int y, const Color map[]) : Image(x, y) {
		for (int i = 0; i < x_size * y_size; i++) {
			contents[i] = map[i];
		}
	}

	Color getPixel(unsigned int x, unsigned int y) const {
		if (x < x_size && y < y_size) {
			return contents[x_size * y + x];
		}
		else {
			throw(PixelIndexOutOfBounds());
		}
	}

	void setPixel(unsigned int x, unsigned int y, Color color) {
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
	void fill(Color color) {
		for (int x = 0; x < x_size; x++) {
			for (int y = 0; y < y_size; y++) {
				setPixel(x, y, color);
			}
		}
	}


protected:
	const unsigned int x_size;
	const unsigned int y_size;

	Color* contents;

};