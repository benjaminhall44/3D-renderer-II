#pragma once
#include "Image.h"
#include "perspective.h"
#include "Sculpture.h"
#include "Matrix.h"
#include "PixelPoint.h"



class Render {
public:
	Render(Image* Screen);
	void RenderWorld(const Perspective& view, const Sculpture& world);
	PixelPoint Project(SpaceVector point) const;
	void Print(int x, int y, double depth, Color color);
	SpaceVector getPixelVector(int x, int y);
	bool checkPointDepth(int x, int y, double depth);

	int getScreenX() const { return screen->getSizeX(); }
	int getScreenY() const { return screen->getSizeY(); }

private:
	static constexpr double MAX_DEPTH = DBL_MAX;
	Matrix<double> pixelDepths;
	Image* screen;
	double FOVfactor;
	void RenderSculpture(Orientation orientation, SpaceVector position, Sculpture scnode);
	double getDepth(int x, int y);
};
