#pragma once

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