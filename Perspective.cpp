#include "Perspective.h"
#include "Orientation.h"

Perspective::Perspective(SpaceVector Position, Rotation Rotation) : 
	position(Position), rotation(Rotation) {}

Rotation Perspective::getRotation() const {
	return rotation;
}

SpaceVector Perspective::getPosition() const {
	return position;
}

void Perspective::setRotation(Rotation Rotation) {
	rotation = Rotation;
}
void Perspective::setPosition(SpaceVector Position) {
	position = Position;
}

void Perspective::moveAbs(SpaceVector displacement) {
	position += displacement;
}
void Perspective::moveRel(SpaceVector displacement) {
	// Creates an Orientation from the Rotation and
	// uses it to rotate the given displacement
	Orientation orientation(rotation);
	position += orientation.rotate(displacement);
}

void Perspective::turn(double Yaw, double Pitch, double Roll) {
	rotation.turn(Yaw, Pitch, Roll);
}
