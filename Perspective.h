#pragma once
#include "SpaceVector.h"
#include "Rotation.h"

// Perspectives consist of a position and a rotation angle
// It is used by the renderer
class Perspective {
public:
	Perspective(SpaceVector Position, Rotation Rotation);

	Rotation getRotation() const;
	SpaceVector getPosition() const;

	void setRotation(Rotation rotation);
	void setPosition(SpaceVector position);
	
	// Moves the perspective a relative to the world
	// e.g. North, South, East, West
	void moveAbs(SpaceVector displacement);

	// Moves the perspective relative to its Rotation
	// e.g. Forward, Backward, Left, Right
	// Positive Z is forward
	// Positive X is left
	// Positive Y is upward
	void moveRel(SpaceVector displacement);

	// Adds to the Rotation of the Perspective
	void turn(double Yaw, double Pitch, double Roll);

private:
	SpaceVector position;
	Rotation rotation;
};