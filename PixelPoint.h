#pragma once

// Contains data describing the location of a pixel on or off the screen
// x, y are the pixel coordinates (may be off the screen)
// depth is the distance the pixel is in front of the screen
// onScreen is true if x, y are within the screen whether the pixel is visible or not
// isFront is true if depth is greater than 0
struct PixelPoint {
	int x, y;
	double depth;
	bool onScreen, inFront;
	PixelPoint(int x, int y, double depth=1, bool onScreen=true, bool inFront=true) {
		this->x = x;
		this->y = y;
		this->depth = depth;
		this->onScreen = onScreen;
		this->inFront = inFront;
	}
	PixelPoint() {
		x = 0;
		y = 0;
		depth = 0;
		onScreen = false;
		inFront = false;
	}
};