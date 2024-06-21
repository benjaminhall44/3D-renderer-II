#include "Perspective.h"
#include "math.h"

Rotation Perspective::getRotation() const {
	SpaceVector K = SpaceVector(cos(-pitch) * sin(-yaw), sin(-pitch), cos(-pitch) * cos(-yaw)); // Forward
	SpaceVector J = SpaceVector(sin(-pitch) * sin(-yaw), cos(-pitch), sin(-pitch) * cos(-yaw)); // Up
	SpaceVector I = K / J;

	return Rotation(I, J, K);
}

SpaceVector Perspective::getPosition() const {
	return position;
}