#include "Perspective.h"
#include "Orientation.h"

Rotation Perspective::getRotation() const {
	return rotation;
}

SpaceVector Perspective::getPosition() const {
	return position;
}


void Perspective::moveAbs(SpaceVector displacement) {
	position += displacement;
}
void Perspective::moveRel(SpaceVector displacement) {
	Orientation orientation(rotation);

	position += orientation.rotate(displacement);
}

void Perspective::turn(double Yaw, double Pitch, double Roll) {
	rotation.turn(Yaw, Pitch, Roll);
}
