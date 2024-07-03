#include "Sculpture.h"
#include "RectangularSculptureElement.h"

Sculpture::Sculpture(
	SpaceVector Displacement,
	Rotation rotation,
	vector<SculptureElement*> Elements,
	vector<Sculpture*> Children) :
	position(Displacement), 
	rotation(rotation), 
	elements(Elements), 
	children(Children)
{}

Sculpture::~Sculpture() {
	for (SculptureElement* e : elements) {
		delete e;
	}
	for (Sculpture* s : children) {
		delete s;
	}
}

const std::vector<SculptureElement*>& Sculpture::getElements() const {
	return elements;
}
const std::vector<Sculpture*> Sculpture::getChildren() const {
	return children;
}
SpaceVector Sculpture::getPosition() const {
	return position;
}
Orientation Sculpture::getRotation() const {
	return Orientation(rotation);
}

Sculpture* Sculpture::Cube(double side, Image* face, SpaceVector Displacement, Rotation rotation) { // Image for 6 identical sides
	Image* faces[] = { face, face, face, face, face, face };
	
	return Cube(side, faces, Displacement, rotation);
}
Sculpture* Sculpture::Cube(double side, Image * *face, SpaceVector Displacement, Rotation rotation) { // 6 Images one for each side
	double radius = side / 2;
	SpaceVector NEU = SpaceVector(radius, radius, radius);
	SpaceVector NED = SpaceVector(radius, -radius, radius);
	SpaceVector NWU = SpaceVector(-radius, radius, radius);
	SpaceVector NWD = SpaceVector(-radius, -radius, radius);

	SpaceVector SEU = SpaceVector(radius, radius, -radius);
	SpaceVector SED = SpaceVector(radius, -radius, -radius);
	SpaceVector SWU = SpaceVector(-radius, radius, -radius);
	SpaceVector SWD = SpaceVector(-radius, -radius, -radius);

	vector<SculptureElement*> faces;
	faces.push_back(new rescel(NEU, NWU, NED, face[0])); // North face
	faces.push_back(new rescel(SWU, SEU, SWD, face[1])); // South face
	faces.push_back(new rescel(SEU, NEU, SED, face[2])); // East face
	faces.push_back(new rescel(NWU, SWU, NWD, face[3])); // West face
	faces.push_back(new rescel(NEU, NWU, SEU, face[4])); // Up face
	faces.push_back(new rescel(SED, SWD, NED, face[5])); // Down face

	return new Sculpture(Displacement, rotation, faces);

}

void Sculpture::setPosition(SpaceVector pos) {
	position = pos;
}
void Sculpture::move(SpaceVector displacement) {
	position += displacement;
}

void Sculpture::setRotation(Rotation rot) {
	rotation = rot;
}
void Sculpture::rotate(Rotation angle) {
	rotation.turn(angle);
}

void Sculpture::addChild(Sculpture* child) {
	children.push_back(child);
}
void Sculpture::addElement(SculptureElement* element) {
	elements.push_back(element);
}

void Sculpture::removeChild(Sculpture* child) {
	bool found = false;
	for (int i = 0; i < children.size(); i++) {
		if (found) {
			children[i - 1] = children[i];
		} 
		else if (children[i] == child) {
			found = true;
		}
	}
	if (found) {
		children.resize(children.size() - 1);
	}

	
}
void Sculpture::removeElement(SculptureElement* element) {
	bool found = false;
	for (int i = 0; i < elements.size(); i++) {
		if (found) {
			elements[i - 1] = elements[i];
		}
		else if (elements[i] == element) {
			found = true;
		}
	}
	if (found) {
		elements.resize(elements.size() - 1);
	}
}