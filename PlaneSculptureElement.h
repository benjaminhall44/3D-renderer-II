#pragma once
#include "SculptureElement.h"
#include "Image.h"
#include "SpaceVector.h"
#include "Rotation.h"
#include <vector>
#include "PixelPoint.h"

class Render;

class PlaneSculptureElement : public SculptureElement {
public:
	PlaneSculptureElement(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis, const Image* texture);

	virtual PlaneSculptureElement* adjust(SpaceVector move, Rotation turn) override;

	virtual void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible) override;

	virtual SpaceVector traceRay(const SpaceVector ray);
	virtual pixel pointColor(SpaceVector point, bool& flag);
protected:
	virtual bool onSurface(double px, double py) = 0;
	virtual std::vector<PixelPoint> getEnds() = 0;
	virtual pixel pointColor(double px, double py) = 0;
	TriscelData* preRender();
	const Image* texture;
private:
	TriscelData* data;
	SpaceVector a;
	SpaceVector b;
	SpaceVector c;
};
