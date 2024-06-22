#pragma once
#include "SculptureElement.h"
#include "Image.h"
#include "SpaceVector.h"
#include "Rotation.h"
#include "RescelData.h"

class Render;

class RectangularSculptureElement : public SculptureElement {
public:
	RectangularSculptureElement(SpaceVector A, SpaceVector B, SpaceVector C, const Image* texture);

	RectangularSculptureElement* adjust(SpaceVector move, Rotation turn);

	void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible);

	SpaceVector traceRay(const SpaceVector ray);
	pixel pointColor(SpaceVector point, bool& flag);
private:
	RescelData* preRender();

	const Image* texture;
	RescelData* data;
	SpaceVector a;
	SpaceVector b;
	SpaceVector c;

};

typedef RectangularSculptureElement rescel;
