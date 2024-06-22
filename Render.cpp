#include "Render.h"
#include "Matrix.h"
#include "PixelPoint.h"

Render::Render(Image* Screen) : screen(Screen), pixelDepths(Screen->getSizeX(), Screen->getSizeY()), FOVfactor(1.0) {}

void Render::RenderWorld(const Perspective& view, const Sculpture& world) {
	pixelDepths.setAll(MAX_DEPTH);
	
	Rotation rotation = view.getRotation();
	SpaceVector position = view.getPosition() * -1;

	RenderSculpture(rotation, position, world);
}

void Render::RenderSculpture(Rotation rotation, SpaceVector position, Sculpture scnode) {
	for (SculptureElement* element : scnode.getElements()) {
		SculptureElement* observed = element->adjust(position, rotation);

		int xmax = 0, xmin = 0, ymax = 0, ymin = 0;
		bool visible = true;

		observed->getCorners(*this, xmax, xmin, ymax, ymin, visible);

		if (visible) {
			for (int x = xmin; x <= xmax; x++) {
				for (int y = ymin; y <= ymax; y++) {
					SpaceVector point = observed->traceRay(getPixelVector(x, y));
					if (point.getZ() > 0 && checkPointDepth(x, y, point.getZ())) {
						bool flag;
						pixel color = observed->pointColor(point, flag);
						if (flag) {
							Print(x, y, point.getZ(), color);
						}
					}
				}
			}
		}
	}
	for (Sculpture chnode : scnode.getChildren()) {
		RenderSculpture(rotation.merge(chnode.getRotation()), position + rotation.rotate(chnode.getPosition()), chnode);
	}
}

PixelPoint Render::Project(SpaceVector point) const {
	if (point.z > 0) {
		int x = FOVfactor * (point.x / point.z + 0.5) * screen->getSizeX();
		int y = FOVfactor * (point.y / point.z + 0.5) * screen->getSizeY();

		if (x >= 0 && x < screen->getSizeX() && 
			y >= 0 && y < screen->getSizeY()) {
			return PixelPoint(x, y, point.z, true, true);
		}
		return PixelPoint(x, y, false);
	}
	else {
		int x = FOVfactor * (point.x / point.z + 0.5) * screen->getSizeX();
		int y = FOVfactor * (point.y / point.z + 0.5) * screen->getSizeY();

		if (x >= 0 && x < screen->getSizeX() &&
			y >= 0 && y < screen->getSizeY()) {
			return PixelPoint(x, y, point.z, true, false);
		}
		return PixelPoint(x, y, point.z, false, false);
	}
}

void Render::Print(int x, int y, double depth, pixel color) {
	if (depth < pixelDepths.at(x, y)) {
		screen->setPixel(x, y, color);
		pixelDepths.at(x, y) = depth;
	}
}

SpaceVector Render::getPixelVector(int x, int y) {
	return SpaceVector(double(x) / screen->getSizeX() / FOVfactor - .5, -(double(y) / screen->getSizeY() / FOVfactor - .5), 1.0);
}

double Render::getDepth(int x, int y) {
	return pixelDepths.at(x, y);
}

bool Render::checkPointDepth(int x, int y, double depth) {
	return depth < getDepth(x, y);
}
