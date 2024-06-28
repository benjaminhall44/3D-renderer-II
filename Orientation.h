#pragma once
#include "SpaceVector.h"
#include "Rotation.h"

class Orientation {
public:
	Orientation(SpaceVector x_axis, SpaceVector y_axis, SpaceVector z_axis) : i(x_axis), j(y_axis), k(z_axis) {};
	Orientation(Rotation rotation);
	Orientation(double yaw, double pitch, double roll);
	Orientation merge(const Orientation& addend) const;
	SpaceVector rotate(const SpaceVector& displacement) const;
private:
	SpaceVector i, j, k;
};

const Orientation MAINAXIS(IVECTOR, JVECTOR, KVECTOR);
