#pragma once

// Contains a 3 bytes rgb color
class Color {
public:
	Color() : red(0), green(0), blue(0) {}

	Color(int r, int g, int b) : red(r), green(g), blue(b) {}

	unsigned char red;
	unsigned char green;
	unsigned char blue;

};

const Color RED = Color(255, 0, 0);
const Color GREEN = Color(0, 255, 0);
const Color BLUE = Color(0, 0, 255);
const Color WHITE = Color(255, 255, 255);
const Color BLACK = Color(0, 0, 0);
