#pragma once

class pixel {
public:
	pixel() : red(0), green(0), blue(0) {}

	pixel(int r, int g, int b) : red(r), green(g), blue(b) {}

	unsigned char red;
	unsigned char green;
	unsigned char blue;

private:
	

};