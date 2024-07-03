#pragma once
#include "SpaceVector.h"
#include "Rotation.h"

// An Orientation is set of rotated axis
// It contains 3 perpendicular unit vectors that
// our used to convert a rotated relative position into
// a real position in space
class Orientation {
public:
	Orientation(SpaceVector x_axis, SpaceVector y_axis, SpaceVector z_axis);

	// Creates an Orientation from a Rotation
	// k is forward
	Orientation(Rotation rotation);
	// Creates an Orientation from a Rotation
	// k is forward
	Orientation(double yaw, double pitch, double roll);

	// Adds another Orientation such that rotating
	// using the new Orientation is the same as rotating with one
	// and then the other
	Orientation merge(const Orientation& addend) const;

	// Evaluates a rotated relative position on this Orientation into a real position in space
	SpaceVector rotate(const SpaceVector& displacement) const;

	// Create an Orientation such that the new Orientation 
	// if merged with the original Orientation 
	// it produces a non-rotated Orientation
	Orientation inverse() const;
private:
	SpaceVector i, j, k;
};

// A non-rotated Orientation
const Orientation MAINAXIS(IVECTOR, JVECTOR, KVECTOR);
