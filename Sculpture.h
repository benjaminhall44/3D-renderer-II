#pragma once

#include "TriangularSculptureElement.h"
#include <vector>


using namespace std;

class Sculpture {
public:
	Sculpture(SpaceVector Displacement = ZEROVECTOR, Rotation rotation = MAINAXIS, vector<triscel> elements = {}, vector<Sculpture> children = {});

	static Sculpture Cube(double side, Image* face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = MAINAXIS); // Image for 6 identical sides
	static Sculpture Cube(double side, Image** face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = MAINAXIS); // 6 Images one for each side

	std::vector<triscel>& getElements() {
		return elements;
	}
	std::vector<Sculpture> getChildren() {
		return children;
	}
	SpaceVector getPosition() {
		return position;
	}
	Rotation getRotation() { 
		return rotation; 
	}
private:
	SpaceVector position;
	Rotation rotation;

	vector<triscel> elements;

	vector<Sculpture> children;
};