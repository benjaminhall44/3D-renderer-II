#pragma once
#include "Image.h"
#include "perspective.h"
#include "Sculpture.h"
#include "Matrix.h"
#include "PixelPoint.h"


// Utility for 3D renderering
// It is constructed by giving it a pointer to an image
// representing the screen
// Only RenderWorld(view, world) is used by a program
class Render {
public:
	Render(Image* Screen);
	// Draws the Sculpture world as seen from the Perspective view
	// onto its associated screen image
	void RenderWorld(const Perspective& view, const Sculpture& world);

	// Functions only used by SculptureElements

	// Gives the pixel location of a point in space
	// This used by SculptureElements for getCorners
	PixelPoint Project(SpaceVector point) const;

	// Adds the color pixel to the pixel location x,y
	// if the current depth their is greater than depth
	void Print(int x, int y, double depth, Color color);

	// Returns the width of the screen
	int getScreenX() const { return screen->getSizeX(); }
	// Returns the height of the screen
	int getScreenY() const { return screen->getSizeY(); }

private:
	static constexpr double MAX_DEPTH = DBL_MAX;
	Matrix<double> pixelDepths;
	Image* screen;
	double FOVfactor;

	// Nesting function for rendering sculptures
	void RenderSculpture(Orientation orientation, SpaceVector position, const Sculpture* scnode);

	// Gives the vector direction that a given pixel is looking in
	SpaceVector getPixelVector(int x, int y);

	// Gets the depth of a pixel
	// the distance to what is visible in that pixel
	double getDepth(int x, int y);

	// Returns false if the pixel x, y is displaying something
	// nearer than the given depth
	bool checkPointDepth(int x, int y, double depth);
};
