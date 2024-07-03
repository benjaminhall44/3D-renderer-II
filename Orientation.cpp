#include "Orientation.h"
#include "math.h"

Orientation::Orientation(SpaceVector x_axis, SpaceVector y_axis, SpaceVector z_axis) : i(x_axis), j(y_axis), k(z_axis) {};

Orientation::Orientation(double yaw, double pitch, double roll) {
	// Pre-calculate repeated sin/cos values
	double sinp = sin(pitch);
	double cosp = cos(pitch);
	double siny = sin(yaw);
	double cosy = cos(yaw);
	double sinr = sin(roll);
	double cosr = cos(roll);

	// k represents forward it goes forward and to the side based on yaw
	// and up based on pitch
	k = SpaceVector(cosp * siny, sinp, cosp * cosy);

	// j represents upward it determined by
	// cos(roll) * (k with pitch + pi/2) + sin(roll) * (k with yaw + pi/2 and pitch = 0)
	// it creates two axes one up with no roll and one up with pi/2 roll and
	// uses roll determine distance allong those axes
	j = SpaceVector(
		-sinp * siny * cosr + cosy * sinr,
		cosp * cosr,
		-sinp * cosy * cosr - siny * sinr
	);
	// i is perpendicular to both k and j
	i = k / j;
}

Orientation::Orientation(Rotation rotation) : Orientation(rotation.getYaw(), rotation.getPitch(), rotation.getRoll()) {}

Orientation Orientation::merge(const Orientation& addend) const {
	// Each new value sums what could contribute to it
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
	// Each part of the relative position is multiplied by the new unit vector
	// Replaces basic unit vectors with ones in this orientation
	return (i * displacement.getX()) + (j * displacement.getY()) + (k * displacement.getZ());
}

Orientation Orientation::inverse() const {
	// Flips values such that X components go into i according to where they were from etc.
	SpaceVector si(i.getX(), j.getX(), k.getX());
	SpaceVector sj(i.getY(), j.getY(), k.getY());
	SpaceVector sk(i.getZ(), j.getZ(), k.getZ());
	return Orientation(si, sj, sk);
}