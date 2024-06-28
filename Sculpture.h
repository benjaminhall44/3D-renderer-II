#pragma once

#include "SculptureElement.h"
#include "Orientation.h"
#include "SpaceVector.h"
#include <vector>


using namespace std;

class Sculpture {
public:
	Sculpture(SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD, vector<SculptureElement*> elements = {}, vector<Sculpture> children = {});

	static Sculpture Cube(double side, Image* face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD); // Image for 6 identical sides
	static Sculpture Cube(double side, Image** face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD); // 6 Images one for each side

	std::vector<SculptureElement*>& getElements();
	std::vector<Sculpture> getChildren();
	SpaceVector getPosition();
	Orientation getRotation();

private:
	SpaceVector position;
	Rotation rotation;

	vector<SculptureElement*> elements;
	vector<Sculpture> children;
};
