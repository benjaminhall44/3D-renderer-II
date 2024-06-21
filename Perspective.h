#pragma once
#include "Rotation.h"

class Perspective {
public:
	Perspective(SpaceVector Position, double Yaw, double Pitch, double Roll) : 
		position(Position), yaw(Yaw), pitch(Pitch), roll(Roll) {}

	Rotation getRotation() const;
	SpaceVector getPosition() const;

private:
	SpaceVector position;
	double yaw;
	double pitch;
	double roll;
};