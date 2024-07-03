#include "Orientation.h"
#include "math.h"

Orientation::Orientation(double yaw, double pitch, double roll) {
	k = SpaceVector(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw)); // Forward
	j = SpaceVector(
		-sin(pitch) * sin(yaw) * cos(roll) + cos(yaw) * sin(roll),
		cos(pitch) * cos(roll),
		-sin(pitch) * cos(yaw) * cos(roll) - sin(yaw) * sin(roll)
	); // Up

	i = k / j;
}

Orientation::Orientation(Rotation rotation) : Orientation(rotation.getYaw(), rotation.getPitch(), rotation.getRoll()) {}

Orientation Orientation::merge(const Orientation& addend) const {
	double six = i.getX() * addend.i.getX() + j.getX() * addend.i.getY() + k.getX() * addend.i.getZ();
	double siy = i.getY() * addend.i.getX() + j.getY() * addend.i.getY() + k.getY() * addend.i.getZ();
	double siz = i.getZ()* addend.i.getX() + j.getZ() * addend.i.getY() + k.getZ() * addend.i.getZ();

	double sjx = i.getX() * addend.j.getX() + j.getX() * addend.j.getY() + k.getX() * addend.j.getZ();
	double sjy = i.getY() * addend.j.getX() + j.getY() * addend.j.getY() + k.getY() * addend.j.getZ();
	double sjz = i.getZ() * addend.j.getX() + j.getZ() * addend.j.getY() + k.getZ() * addend.j.getZ();

	double skx = i.getX() * addend.k.getX() + j.getX() * addend.k.getY() + k.getX() * addend.k.getZ();
	double sky = i.getY() * addend.k.getX() + j.getY() * addend.k.getY() + k.getY() * addend.k.getZ();
	double skz = i.getZ() * addend.k.getX() + j.getZ() * addend.k.getY() + k.getZ() * addend.k.getZ();

	SpaceVector si(six, siy, siz);
	SpaceVector sj(sjx, sjy, sjz);
	SpaceVector sk(skx, sky, skz);

	return Orientation(si, sj, sk);
}

SpaceVector Orientation::rotate(const SpaceVector& displacement) const {
	return (i * displacement.getX()) + (j * displacement.getY()) + (k * displacement.getZ());
}
