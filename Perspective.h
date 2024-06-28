#pragma once
#include "SpaceVector.h"
#include "Rotation.h"

class Perspective {
public:
	Perspective(SpaceVector Position, Rotation Rotation) : position(Position), rotation(Rotation) {}

	Rotation getRotation() const;
	SpaceVector getPosition() const;
	
	void moveAbs(SpaceVector displacement);
	void moveRel(SpaceVector displacement);

	void turn(double Yaw, double Pitch, double Roll);

private:
	SpaceVector position;
	Rotation rotation;
};