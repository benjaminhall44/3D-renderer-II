#include "RectangularSculptureElement.h"

RectangularSculptureElement::RectangularSculptureElement(SpaceVector leftTop, SpaceVector rightTop, SpaceVector leftBottom, const Image* Texture) : 
	PlaneSculptureElement(leftTop, rightTop, leftBottom),
	texture(Texture) {
}


PlaneSculptureElement* RectangularSculptureElement::getNew(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis) {
	return new RectangularSculptureElement(origin, xaxis, yaxis, texture);
}
bool RectangularSculptureElement::onSurface(double px, double py) {
	// Point is within a positive 1x1 square from (0,0) to (1,1)
	return px >= 0 && px < 1 && py >= 0 && py < 1;
}
std::vector<PlaneSculptureElement::PlanePoint> RectangularSculptureElement::getEnds() {
	// Return the four corners
	return std::vector<PlaneSculptureElement::PlanePoint>({ PlanePoint(0, 0), PlanePoint(1, 0), PlanePoint(0, 1), PlanePoint(1, 1) });
}

Color RectangularSculptureElement::pointColor(double px, double py) {
	// Multiply point values by texture length/width to determine pixel on surface
	int Tx = (int) (px * texture->getSizeX());
	int Ty = (int) (py * texture->getSizeY());
	return texture->getPixel(Tx, Ty);
}