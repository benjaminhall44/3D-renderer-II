#pragma once
#include "PlaneSculptureElement.h"
#include "Image.h"

class Render;

class RectangularSculptureElement : public PlaneSculptureElement {
public:
	RectangularSculptureElement(SpaceVector leftTop, SpaceVector rightTop, SpaceVector leftBottom, const Image* Texture);

protected:
	virtual PlaneSculptureElement* getNew(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis) override;
	virtual bool onSurface(double px, double py) override;
	virtual std::vector<PlanePoint> getEnds() override;
	virtual pixel pointColor(double px, double py) override;
private:
	const Image* texture;

};

typedef RectangularSculptureElement rescel;
