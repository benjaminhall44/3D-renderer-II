#include "Image.h"

Image::Image(const unsigned int x, const unsigned int y) : x_size(x), y_size(y) {
	contents = new Color[x_size * y_size];
}

Image::Image(const unsigned int x, const unsigned int y, const Color map[]) : Image(x, y) {
	int size = x_size * y_size;
	for (int i = 0; i < size; i++) {
		contents[i] = map[i];
	}
}

Image::~Image() {
	delete contents;
}

Color Image::getPixel(unsigned int x, unsigned int y) const {
	if (x < x_size && y < y_size) {
		return contents[x_size * y + x];
	}
	else {
		throw(PixelIndexOutOfBounds());
	}
}

void Image::setPixel(unsigned int x, unsigned int y, Color color) {
	if (x < x_size && y < y_size) {
		contents[x_size * y + x] = color;
	}
	else {
		throw(PixelIndexOutOfBounds());
	}
}

int Image::getSizeX() const {
	return x_size;
}

int Image::getSizeY() const {
	return y_size;
}
void Image::fill(Color color) {
	int size = x_size * y_size;
	for (int i = 0; i < size; i++) {
		contents[i] = color;
	}
}
