#pragma once
#include "PlaneSculptureElement.h"
#include "Image.h"

class Render;

// A PlaneSculptureElement containing a triangle
class TriangularSculptureElement : public PlaneSculptureElement {
public:
	TriangularSculptureElement(SpaceVector A, SpaceVector B, SpaceVector C, const Image* texture);

protected:
	virtual PlaneSculptureElement* getNew(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis) override;
	virtual bool onSurface(double px, double py) override;
	virtual std::vector<PlanePoint> getEnds() override;
	virtual Color pointColor(double px, double py) override;
private:
	const Image* texture;

};

typedef TriangularSculptureElement triscel;
