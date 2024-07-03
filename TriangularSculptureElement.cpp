#include "TriangularSculptureElement.h"

TriangularSculptureElement::TriangularSculptureElement(SpaceVector A, SpaceVector B, SpaceVector C, const Image* Texture) :
	PlaneSculptureElement(C, A, B),
	texture(Texture) {
}


PlaneSculptureElement* TriangularSculptureElement::getNew(SpaceVector origin, SpaceVector xaxis, SpaceVector yaxis) {
	return new TriangularSculptureElement(xaxis, yaxis, origin, texture);
}
bool TriangularSculptureElement::onSurface(double px, double py) {
	// Point is within a triangle
	return px >= 0 && px < 1 && py >= 0 && py < px;
}
std::vector<PlaneSculptureElement::PlanePoint> TriangularSculptureElement::getEnds() {
	// Return the three corners
	return std::vector<PlaneSculptureElement::PlanePoint>({ PlanePoint(0, 0), PlanePoint(1, 0), PlanePoint(0, 1) });
}

Color TriangularSculptureElement::pointColor(double px, double py) {
	// Multiply point values by texture length/width to determine pixel on surface
	int Tx = px * texture->getSizeX();
	int Ty = py * texture->getSizeY();
	return texture->getPixel(Tx, Ty);
}