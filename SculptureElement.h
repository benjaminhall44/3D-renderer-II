#pragma once
#include "Image.h"
#include "SpaceVector.h"
#include "Rotation.h"

class Render;

class SculptureElement {
public:
	virtual SculptureElement* adjust(SpaceVector move, Rotation turn) = 0;

	virtual void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible)=0;

	virtual SpaceVector traceRay(const SpaceVector ray)=0;
	virtual pixel pointColor(SpaceVector point, bool& flag)=0;
};


