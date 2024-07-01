#include "PlaneSculptureElement.h"
#include "Render.h"

PlaneSculptureElement::PlaneSculptureElement(SpaceVector Origin, SpaceVector Xaxis, SpaceVector Yaxis) : origin(Origin), xaxis(Xaxis), yaxis(Yaxis), extraCalculations(nullptr) {}

SculptureElement* PlaneSculptureElement::adjust(SpaceVector move, Orientation turn) {
	plascel* adjusted = this->getNew(move + turn.rotate(origin), move + turn.rotate(xaxis), move + turn.rotate(yaxis));
	adjusted->extraCalculations = (PlascelData*)(adjusted->preRender());
	return adjusted;
}

PlascelData* PlaneSculptureElement::preRender() {
	return new PlascelData(origin, xaxis, yaxis);
}

void PlaneSculptureElement::getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible) {
	std::vector<PlanePoint> ends = getEnds();
	std::vector<PixelPoint> corners;
	for (PlanePoint p : ends) {
		corners.push_back(rendering.Project(origin + extraCalculations->xArm * p.Px + extraCalculations->yArm * p.Py));
	}


	visible = false;
	for (PixelPoint corner : corners) {
		if (corner.inFront) {
			visible = true;
			break;
		}
	}

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

	for (PixelPoint corner : corners) {
		if (!corner.inFront) {
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


	if (xmax == xmin || ymax == ymin) {
		visible = false;
		return;
	}
}

SpaceVector PlaneSculptureElement::traceRay(const SpaceVector ray) {
	return ray * (extraCalculations->planeConstant / (ray * extraCalculations->normal));
}

Color PlaneSculptureElement::pointColor(SpaceVector point, bool& flag) {
	point -= origin;
	double Px = (point * extraCalculations->xPrime) / extraCalculations->xPrime.squared();
	double Py = ((point - extraCalculations->xArm * Px) * extraCalculations->yArm) / extraCalculations->yArm.squared();

	// Determine pixel coords
	if (onSurface(Px, Py)) {
		flag = true;
		return pointColor(Px, Py);
	}
	else {
		flag = false;
		return Color();
	}
}