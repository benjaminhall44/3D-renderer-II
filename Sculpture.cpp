#include "Sculpture.h"
#include "RectangularSculptureElement.h"

Sculpture::Sculpture(
	SpaceVector Displacement,
	Rotation rotation,
	vector<SculptureElement*> Elements,
	vector<Sculpture> Children) :
	position(Displacement), 
	rotation(rotation), 
	elements(Elements), 
	children(Children)
{}

std::vector<SculptureElement*>& Sculpture::getElements() {
	return elements;
}
std::vector<Sculpture> Sculpture::getChildren() {
	return children;
}
SpaceVector Sculpture::getPosition() {
	return position;
}
Orientation Sculpture::getRotation() {
	return Orientation(rotation);
}

Sculpture Sculpture::Cube(double side, Image* face, SpaceVector Displacement, Rotation rotation) { // Image for 6 identical sides
	Image* faces[] = { face, face, face, face, face, face };
	
	return Cube(side, faces, Displacement, rotation);
}
Sculpture Sculpture::Cube(double side, Image * *face, SpaceVector Displacement, Rotation rotation) { // 6 Images one for each side
	double radius = side / 2;
	SpaceVector NEU = Displacement + SpaceVector(radius, radius, radius);
	SpaceVector NED = Displacement + SpaceVector(radius, -radius, radius);
	SpaceVector NWU = Displacement + SpaceVector(-radius, radius, radius);
	SpaceVector NWD = Displacement + SpaceVector(-radius, -radius, radius);

	SpaceVector SEU = Displacement + SpaceVector(radius, radius, -radius);
	SpaceVector SED = Displacement + SpaceVector(radius, -radius, -radius);
	SpaceVector SWU = Displacement + SpaceVector(-radius, radius, -radius);
	SpaceVector SWD = Displacement + SpaceVector(-radius, -radius, -radius);

	vector<SculptureElement*> faces;
	faces.push_back(new rescel(NEU, NWU, NED, face[0])); // North face
	faces.push_back(new rescel(SWU, SEU, SWD, face[1])); // South face
	faces.push_back(new rescel(SEU, NEU, SED, face[2])); // East face
	faces.push_back(new rescel(NWU, SWU, NWD, face[3])); // West face
	faces.push_back(new rescel(NEU, NWU, SEU, face[4])); // Up face
	faces.push_back(new rescel(SED, SWD, NED, face[5])); // Down face

	return Sculpture(Displacement, rotation, faces);

}
