#pragma once
#include "Rotation.h"

class Perspective {
public:
	Perspective(SpaceVector Position, double Yaw, double Pitch, double Roll) : 
		position(Position), yaw(Yaw), pitch(Pitch), roll(Roll) {}

	Rotation getRotation() const;
	SpaceVector getPosition() const;
	
	void moveAbs(SpaceVector displacement);
	void moveRel(SpaceVector displacement);

	void turnAbs(double Yaw, double Pitch, double Roll);
	void turnRel(double Yaw, double Pitch, double Roll);

private:
	static double normalizeAngle(double angle);

	SpaceVector position;
	double yaw;
	double pitch;
	double roll;
};