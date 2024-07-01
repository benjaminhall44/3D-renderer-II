#pragma once
#include "SculptureElement.h"
#include "Image.h"
#include "SpaceVector.h"
#include "Rotation.h"
#include "TriscelData.h"

class Render;

class TriangularSculptureElement : public SculptureElement {
public:
	TriangularSculptureElement(SpaceVector A, SpaceVector B, SpaceVector C, const Image* texture);

	virtual TriangularSculptureElement* adjust(SpaceVector move, Orientation turn);

	virtual void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible);

	virtual SpaceVector traceRay(const SpaceVector ray);
	virtual Color pointColor(SpaceVector point, bool& flag);
protected:
	
private:
	TriscelData* preRender();
	const Image* texture;
	TriscelData* data;
	SpaceVector a;
	SpaceVector b;
	SpaceVector c;
	//
};

typedef TriangularSculptureElement triscel;
