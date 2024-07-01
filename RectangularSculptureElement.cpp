#include "RectangularSculptureElement.h"

RectangularSculptureElement::RectangularSculptureElement(SpaceVector leftTop, SpaceVector rightTop, SpaceVector leftBottom, const Image* Texture) : 
	PlaneSculptureElement(leftTop, rightTop, leftBottom),
	texture(Texture) {
}


PlaneSculptureElement* RectangularSculptureElement::getNew(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis) {
	return new RectangularSculptureElement(origin, xaxis, yaxis, texture);
}
bool RectangularSculptureElement::onSurface(double px, double py) {
	return px >= 0 && px < 1 && py >= 0 && py < 1;
}
std::vector<PlaneSculptureElement::PlanePoint> RectangularSculptureElement::getEnds() {
	return std::vector<PlaneSculptureElement::PlanePoint>({ PlanePoint(0, 0), PlanePoint(1, 0), PlanePoint(0, 1), PlanePoint(1, 1) });
}

Color RectangularSculptureElement::pointColor(double px, double py) {
	int Tx = px * texture->getSizeX();
	int Ty = py * texture->getSizeY();
	return texture->getPixel(Tx, Ty);
}