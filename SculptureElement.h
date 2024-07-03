#pragma once
#include "Image.h"
#include "SpaceVector.h"
#include "Orientation.h"

class Render;

// SculptureElements are the visual elements of Sculptures
// They contain data describing the position and appearance of a visual element
class SculptureElement {
public:
	// Creates a new SculptureElement with its location vectors relative to
	// the position move and the orientation turn
	virtual SculptureElement* adjust(SpaceVector move, Orientation turn) = 0;

	// Calculates the corners of the segment of screen on which the element is visible
	// This helps to save work by limiting the number of pixel calculations
	virtual void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible)=0;

	// Returns the nearest location at which the given vector intersects the element
	virtual SpaceVector traceRay(const SpaceVector ray)=0;

	// Calculates the color for a specific point on a SculptureElement
	// onSurface is false when the point is not on the element
	virtual Color pointColor(SpaceVector point, bool& onSurface)=0;
};


