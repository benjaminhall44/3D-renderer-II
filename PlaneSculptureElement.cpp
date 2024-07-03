#include "PlaneSculptureElement.h"
#include "Render.h"

PlaneSculptureElement::PlaneSculptureElement(SpaceVector Origin, SpaceVector Xaxis, SpaceVector Yaxis) : origin(Origin), xaxis(Xaxis), yaxis(Yaxis), extraCalculations(nullptr) {}

SculptureElement* PlaneSculptureElement::adjust(SpaceVector move, Orientation turn) {
	// Create a new element of the same type using virtual getNew function and new location values
	// such that the old location is relative to move and rotated by turn
	plascel* adjusted = this->getNew(move + turn.rotate(origin), move + turn.rotate(xaxis), move + turn.rotate(yaxis));

	// Generates extra calculations to help rendering
	adjusted->extraCalculations = (PlascelData*)(adjusted->preRender());
	return adjusted;
}

PlascelData* PlaneSculptureElement::preRender() {
	return new PlascelData(origin, xaxis, yaxis);
}

void PlaneSculptureElement::getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible) {
	// Generates edge PixelPoints to consider
	std::vector<PlanePoint> ends = getEnds();
	std::vector<PixelPoint> corners;
	for (PlanePoint p : ends) {
		corners.push_back(rendering.Project(origin + extraCalculations->xArm * p.Px + extraCalculations->yArm * p.Py));
	}

	// If all PixelPoints are behind screen the element is not visible
	visible = false;
	for (PixelPoint corner : corners) {
		if (corner.inFront) {
			visible = true;
			break;
		}
	}

	// Calculates the max and min for x and y values in front of the screen
	xmax = corners[0].x;
	xmin = corners[0].x;
	ymax = corners[0].y;
	ymin = corners[0].y;
	for (PixelPoint corner : corners) {
		if (corner.inFront) {
			if (corner.x > xmax) {
				xmax = corner.x;
			}
			if (corner.x < xmin) {
				xmin = corner.x;
			}
			if (corner.y > ymax) {
				ymax = corner.y;
			}
			if (corner.y < ymin) {
				ymin = corner.y;
			}
		}
	}

	// When an element is partially behind the screen the element may be
	// visible all the way to an edge
	for (PixelPoint corner : corners) {
		if (!corner.inFront) {
			// x,y values are negative of normal when z is negative
			if (corner.x > xmax) {
				xmin = 0;
			}
			else {
				xmax = rendering.getScreenX() - 1;
			}
			if (corner.x < xmin) {
				xmax = rendering.getScreenX() - 1;
			}
			else {
				xmin = 0;
			}

			if (corner.y > ymax) {
				ymin = 0;
			}
			else {
				ymax = rendering.getScreenY() - 1;
			}
			if (corner.y < ymin) {
				ymax = rendering.getScreenY() - 1;
			}
			else {
				ymin = 0;
			}
		}
	}

	// Pushes maxs and mins off the screen onto the screen
	if (xmin < 0) {
		xmin = 0;
	}
	if (xmax > rendering.getScreenX() - 1) {
		xmax = rendering.getScreenX() - 1;
	}

	if (ymin < 0) {
		ymin = 0;
	}
	if (ymax > rendering.getScreenY() - 1) {
		ymax = rendering.getScreenY() - 1;
	}

	// If max and min are equal the element is too narrow to be visible
	// or it is off the side of the screen
	if (xmax == xmin || ymax == ymin) {
		visible = false;
		return;
	}
}

SpaceVector PlaneSculptureElement::traceRay(const SpaceVector ray) {
	// Intersection = ray unit vector times the distance to the surface along its normal vector
	// (normal * origin) / (ray * normal)
	return ray * (extraCalculations->planeConstant / (ray * extraCalculations->normal));
}

Color PlaneSculptureElement::pointColor(SpaceVector point, bool& flag) {
	// Calculate how much of each axis vector is needed to reach the given point
	// even when axes are not perpendicular
	point -= origin;
	double Px = (point * extraCalculations->xPrime) * extraCalculations->xPrimeSquaredReciprocal;
	double Py = ((point - extraCalculations->xArm * Px) * extraCalculations->yArm) * extraCalculations->yArmSquaredReciprocal;

	// Check if the point is part of the shape and 
	// return its color if it is
	if (onSurface(Px, Py)) {
		flag = true;
		return pointColor(Px, Py);
	}
	else {
		flag = false;
		return Color();
	}
}