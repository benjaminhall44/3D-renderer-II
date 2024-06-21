#pragma once
#include "SpaceVector.h"

class Rotation {
public:
	Rotation(SpaceVector x_axis, SpaceVector y_axis, SpaceVector z_axis) : i(x_axis), j(y_axis), k(z_axis) {};
	Rotation merge(const Rotation& addend) const;
	SpaceVector rotate(const SpaceVector& displacement) const;
private:
	SpaceVector i, j, k;
};

const Rotation MAINAXIS(IVECTOR, JVECTOR, KVECTOR);
