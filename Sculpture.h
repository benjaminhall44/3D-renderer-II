#pragma once

#include "SculptureElement.h"
#include "Orientation.h"
#include "SpaceVector.h"
#include <vector>


using namespace std;

// Sculptures are nested structures containing graphical elements
// Each sculpture has a position, a rotation, a vector of visible elements, and 
// a vector of sub-sculptures that inherit its position and rotation and add to them
// the positions of sub-sculptures are relative to the rotation and position of the
// parent sculpture
class Sculpture {
public:
	Sculpture(SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD, vector<SculptureElement*> elements = {}, vector<Sculpture*> children = {});

	~Sculpture();

	// Creates a centered cube with six identidal faces
	static Sculpture* Cube(double side, Image* face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD);
	// Creates a centered cube with six unique faces
	static Sculpture* Cube(double side, Image** face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD);

	const std::vector<SculptureElement*>& getElements() const;
	const std::vector<Sculpture*> getChildren() const;
	SpaceVector getPosition() const;
	Orientation getRotation() const;

	void setPosition(SpaceVector pos);
	void move(SpaceVector displacement);

	void setRotation(Rotation rot);
	void rotate(Rotation angle);

	// Adds a sub-sculpture
	void addChild(Sculpture* child);
	// Adds a visual element
	void addElement(SculptureElement* element);

	// Removes a sub-sculpture (does not delete it from the heap)
	void removeChild(Sculpture* child);
	// Removes a visual element
	void removeElement(SculptureElement* element);

private:
	SpaceVector position;
	Rotation rotation;

	vector<SculptureElement*> elements;
	vector<Sculpture*> children;
};
