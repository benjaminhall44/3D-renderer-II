#include "Render.h"
#include "Matrix.h"
#include "PixelPoint.h"

Render::Render(Image* Screen) : screen(Screen), pixelDepths(Screen->getSizeX(), Screen->getSizeY()), FOVfactor(1.0) {}

void Render::RenderWorld(const Perspective& view, const Sculpture& world) {
	// Resets depths to sky distance
	pixelDepths.setAll(MAX_DEPTH);
	
	// Get an inverse Orientation of the Perspectives Rotation so that
	// the world is rotated accordingly
	Orientation orientation = Orientation(view.getRotation()).inverse();

	// Make all positions relative to the perspective
	SpaceVector position = -view.getPosition();

	RenderSculpture(orientation, orientation.rotate(position) /*rotate position so that it matches*/, &world);
}

void Render::RenderSculpture(Orientation orientation, SpaceVector position, const Sculpture* scnode) {
	// Render each visible element
	for (SculptureElement* element : scnode->getElements()) {
		// Create a visible element with positions defined relative to the perspective
		SculptureElement* observed = element->adjust(position, orientation);

		// Ask the element were on the screen it is to save work
		int xmax = 0, xmin = 0, ymax = 0, ymin = 0;
		bool visible = true;
		observed->getCorners(*this, xmax, xmin, ymax, ymin, visible);

		if (visible) {
			// Go through each pixel in the region of the screen checking whether it
			// is on the surface and what color it is
			for (int x = xmin; x <= xmax; x++) {
				for (int y = ymin; y <= ymax; y++) {
					// Determine the position in space at which that pixel is looking on the surface
					SpaceVector point = observed->traceRay(getPixelVector(x, y));
					if (point.getZ() > 0 && checkPointDepth(x, y, point.getZ())) {
						// Determine whether the point is on the surface and what color it is
						bool onSurface;
						Color color = observed->pointColor(point, onSurface);
						if (onSurface) {
							Print(x, y, point.getZ(), color);
						}
					}
				}
			}
		}

		delete observed;
	}
	// Render all sub-sculptures
	for (Sculpture* chnode : scnode->getChildren()) {
		RenderSculpture(orientation.merge(chnode->getRotation()), position + orientation.rotate(chnode->getPosition()), chnode);
	}
}

PixelPoint Render::Project(SpaceVector point) const {
	// Calculate pixel location
	// 0.5 is added because half of the screen is negative
	double xd = FOVfactor * (point.x / point.z + 0.5) * screen->getSizeX();
	double yd = FOVfactor * (-point.y / point.z + 0.5) * screen->getSizeY();

	// Convert to integers
	int x = xd;
	int y = yd;

	// If double pixel values are really large integer conversion creates negative numbers
	// This corrects sign mismatch
	if ((x < 0) ^ (xd < 0)) {
		x *= -1;
	}
	if ((y < 0) ^ (yd < 0)) {
		y *= -1;
	}

	// Returns the PixelPoint with appropriate flags
	if (point.z > 0) {
		if (x >= 0 && x < screen->getSizeX() && 
			y >= 0 && y < screen->getSizeY()) {
			return PixelPoint(x, y, point.z, true, true);
		}
		return PixelPoint(x, y, false, true);
	}
	else {
		if (x >= 0 && x < screen->getSizeX() &&
			y >= 0 && y < screen->getSizeY()) {
			return PixelPoint(x, y, point.z, true, false);
		}
		return PixelPoint(x, y, point.z, false, false);
	}
}

void Render::Print(int x, int y, double depth, Color color) {
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
