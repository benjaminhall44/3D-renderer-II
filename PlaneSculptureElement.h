#pragma once
#include "SculptureElement.h"
#include "Image.h"
#include "SpaceVector.h"
#include "Rotation.h"
#include <vector>
#include "PixelPoint.h"
#include "PlascelData.h"

class Render;

// A visual element of a Sculpture that consists of a shape on a plane in space
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
	// Describes a point on the surface of a PlaneSculptureElement
	struct PlanePoint {
		PlanePoint(double px, double py) : Px(px), Py(py) {};
		double Px;
		double Py;
	};
	// Handles construction of new objects of inheriting classes when it is done in methods
	virtual PlaneSculptureElement* getNew(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis) = 0;

	// Returns true if the described point is within the desired shape
	virtual bool onSurface(double px, double py) = 0;

	// Returns a vector of PlanePoints that corrospond to edges that must be considered
	// to determine how much of the screen the SculptureElement is visible on
	virtual std::vector<PlanePoint> getEnds() = 0;

	// Returns a Color given a point on the PlaneSculptureElements plane surface
	virtual Color pointColor(double px, double py) = 0;
	
private:
	// Returns a pointer to a struct containing useful calculationed values
	// That are used repeatedly when rendering a surface
	PlascelData* preRender();

	// Contains useful calculationed values
	// That are used repeatedly when rendering a surface
	// It is created upon adjusting
	PlascelData* extraCalculations;

	// The 0,0 point on the plain
	SpaceVector origin;

	// The 1,0 point on the plain
	SpaceVector xaxis;

	// The 0,1 point on the plain
	SpaceVector yaxis;
};

typedef PlaneSculptureElement plascel;

