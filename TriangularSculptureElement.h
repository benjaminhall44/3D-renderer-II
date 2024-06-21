#pragma once
#include "Image.h"
#include "SpaceVector.h"
#include "Rotation.h"
#include "TriscelData.h"

class Render;

class TriangularSculptureElement {
public:
	TriangularSculptureElement(SpaceVector A, SpaceVector B, SpaceVector C, const Image* texture);

	TriangularSculptureElement adjust(SpaceVector move, Rotation turn);
	TriscelData preRender();

	void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible);

	SpaceVector traceRay(const SpaceVector ray, TriscelData data);
	pixel pointColor(SpaceVector point, const TriscelData& data, bool& flag);
private:
	const Image* texture;
	SpaceVector a;
	SpaceVector b;
	SpaceVector c;

};

typedef TriangularSculptureElement triscel;
