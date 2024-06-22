#include "TriangularSculptureElement.h"
#include "Render.h"

TriangularSculptureElement::TriangularSculptureElement(SpaceVector A, SpaceVector B, SpaceVector C, const Image* Texture) : a(A), b(B), c(C), texture(Texture) {}

triscel* TriangularSculptureElement::adjust(SpaceVector move, Rotation turn) {
	triscel* adjusted = new triscel(move + turn.rotate(a), move + turn.rotate(b), move + turn.rotate(c), texture);
	adjusted->data = (TriscelData*) (adjusted->preRender());
	return adjusted;
}

TriscelData* TriangularSculptureElement::preRender() {
	return new TriscelData(a, b, c);
}

void TriangularSculptureElement::getCorners(const Render& rendering, int& xmax, int& xmin, int& ymax, int& ymin, bool& visible) {
	PixelPoint corners[3] = {rendering.Project(a) , rendering.Project(b), rendering.Project(c)};
	visible = true;
	if (!corners[0].inFront && !corners[1].inFront && !corners[2].inFront) {
		visible = false;
		return;
	}
	xmax = corners[0].x;
	xmin = corners[0].x;
	ymax = corners[0].y;
	ymin = corners[0].y;
	for (int i = 1; i < 3; i++) {
		if (corners[i].inFront) {
			if (corners[i].x > xmax) {
				xmax = corners[i].x;
			}
			if (corners[i].x < xmin) {
				xmin = corners[i].x;
			}
			if (corners[i].y > ymax) {
				ymax = corners[i].y;
			}
			if (corners[i].y < ymin) {
				ymin = corners[i].y;
			}
		}
	}

	if (!corners[0].inFront || !corners[1].inFront || !corners[2].inFront) {
		for (int i = 0; i < 3; i++) {
			if (!corners[i].inFront){
				if (corners[i].x > xmax) {
					xmin = 0;
				}
				else {
					xmax = rendering.getScreenX() - 1;
				}
				if (corners[i].x < xmin) {
					xmax = rendering.getScreenX() - 1;
				}
				else {
					xmin = 0;
				}

				if (corners[i].y > ymax) {
					ymin = 0;
				}
				else {
					ymax = rendering.getScreenY() - 1;
				}
				if (corners[i].y < ymin) {
					ymax = rendering.getScreenY() - 1;
				}
				else {
					ymin = 0;
				}
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

SpaceVector TriangularSculptureElement::traceRay(const SpaceVector ray) {
	return ray * (data->planeConstant / (ray * data->normal));
}

pixel TriangularSculptureElement::pointColor(SpaceVector point, bool& flag) {
	point -= c;
	double Px = (point * data->bPrime) / data->bPrime.squared();
	double Py = ((point - data->B * Px) * data->A) / data->A.squared();

	// Determine pixel coords
	if (Px >= 0 && Px < 1 && Py >= 0 && Py < Px) {
		unsigned int Tx = (int) (Px * texture->getSizeX());
		unsigned int Ty = (int) (Py * texture->getSizeY());

		flag = true;
		return texture->getPixel(Tx, Ty);
	}
	else {
		flag = false;
		return pixel();
	}
}
