#include "Sculpture.h"

Sculpture::Sculpture(
	SpaceVector Displacement,
	Rotation rotation,
	vector<triscel> Elements,
	vector<Sculpture> Children) :
	position(Displacement), 
	rotation(rotation), 
	elements(Elements), 
	children(Children)
{}

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

	vector<triscel> faces;
	faces.push_back(triscel(NWD, NEU, NED, face[0])); // North face
	faces.push_back(triscel(SED, SWU, SWD, face[1])); // South face
	faces.push_back(triscel(NED, SEU, SED, face[2])); // East face
	faces.push_back(triscel(SWD, NWU, NWD, face[3])); // West face
	faces.push_back(triscel(SEU, NWU, SWU, face[4])); // Up face
	faces.push_back(triscel(NED, SWD, NWD, face[5])); // Down face

	return Sculpture(Displacement, rotation, faces);

}
