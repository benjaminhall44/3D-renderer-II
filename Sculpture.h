#pragma once

#include "SculptureElement.h"
#include "Orientation.h"
#include "SpaceVector.h"
#include <vector>


using namespace std;

class Sculpture {
public:
	Sculpture(SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD, vector<SculptureElement*> elements = {}, vector<Sculpture*> children = {});

	~Sculpture();

	static Sculpture* Cube(double side, Image* face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD); // Image for 6 identical sides
	static Sculpture* Cube(double side, Image** face, SpaceVector Displacement = ZEROVECTOR, Rotation rotation = FORWARD); // 6 Images one for each side

	const std::vector<SculptureElement*>& getElements() const;
	const std::vector<Sculpture*> getChildren() const;
	SpaceVector getPosition() const;
	Orientation getRotation() const;

	void setPosition(SpaceVector pos);
	void move(SpaceVector displacement);

	void setRotation(Rotation rot);
	void rotate(Rotation angle);

	void addChild(Sculpture* child);
	void addElement(SculptureElement* element);

	void removeChild(Sculpture* child);
	void removeElement(SculptureElement* element);

private:
	SpaceVector position;
	Rotation rotation;

	vector<SculptureElement*> elements;
	vector<Sculpture*> children;
};
