#pragma once
#include "Image.h"
#include "SpaceVector.h"
#include "Orientation.h"

class Render;

class SculptureElement {
public:
	virtual SculptureElement* adjust(SpaceVector move, Orientation turn) = 0;

	virtual void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible)=0;

	virtual SpaceVector traceRay(const SpaceVector ray)=0;
	virtual Color pointColor(SpaceVector point, bool& flag)=0;
};


