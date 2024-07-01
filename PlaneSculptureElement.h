#pragma once
#include "SculptureElement.h"
#include "Image.h"
#include "SpaceVector.h"
#include "Rotation.h"
#include <vector>
#include "PixelPoint.h"
#include "PlascelData.h"

class Render;

class PlaneSculptureElement : public SculptureElement {
public:
	PlaneSculptureElement(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis);

	~PlaneSculptureElement() {
		delete extraCalculations;
	}

	virtual SculptureElement* adjust(SpaceVector move, Orientation turn) override;

	virtual void getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible) override;

	virtual SpaceVector traceRay(const SpaceVector ray);
	virtual Color pointColor(SpaceVector point, bool& flag);
protected:
	struct PlanePoint {
		PlanePoint(double px, double py) : Px(px), Py(py) {};
		double Px;
		double Py;
	};
	virtual PlaneSculptureElement* getNew(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis) = 0;
	virtual bool onSurface(double px, double py) = 0;
	virtual std::vector<PlanePoint> getEnds() = 0;
	virtual Color pointColor(double px, double py) = 0;
	
private:
	PlascelData* preRender();
	PlascelData* extraCalculations;
	SpaceVector origin;
	SpaceVector xaxis;
	SpaceVector yaxis;
};

typedef PlaneSculptureElement plascel;

