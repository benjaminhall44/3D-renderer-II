#include "SpaceVector.h"
#include <math.h>;


// Vector addition
SpaceVector SpaceVector::operator+(SpaceVector rhs) const {
	return SpaceVector(x + rhs.x, y + rhs.y, z + rhs.z);
}
SpaceVector& SpaceVector::operator+=(SpaceVector rhs) {
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}
SpaceVector SpaceVector::operator-(SpaceVector rhs) const {
	return SpaceVector(x - rhs.x, y - rhs.y, z - rhs.z);
}
SpaceVector& SpaceVector::operator-=(SpaceVector rhs) {
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
// Vector-scalar multiplication
SpaceVector SpaceVector::operator*(double rhs) const {
	return SpaceVector(x * rhs, y * rhs, z * rhs);
}
SpaceVector& SpaceVector::operator*=(double rhs) {
	x *= rhs;
	y *= rhs;
	z *= rhs;
	return *this;
}
SpaceVector SpaceVector::operator/(double rhs) const {
	return SpaceVector(x / rhs, y / rhs, z / rhs);
}
SpaceVector& SpaceVector::operator/=(double rhs) {
	x /= rhs;
	y /= rhs;
	z /= rhs;
	return *this;
}
// Vector dot product
double SpaceVector::operator*(SpaceVector rhs) const {
	return x * rhs.x + y * rhs.y + z * rhs.z;
}
// Vector cross product
SpaceVector SpaceVector::operator/(SpaceVector rhs) const {
	return SpaceVector(y * rhs.z - z * rhs.y, 
					   z * rhs.x - x * rhs.z, 
					   x * rhs.y - y * rhs.x);
}
SpaceVector& SpaceVector::operator/=(SpaceVector rhs) {
	*this = *this / rhs;
	return *this;
}

bool SpaceVector::operator==(SpaceVector rhs) const {
	return x == rhs.x && y == rhs.y && z == rhs.z;
}
bool SpaceVector::operator>(SpaceVector rhs) const {
	return squared() > rhs.squared();
}
bool SpaceVector::operator<(SpaceVector rhs) const {
	return rhs > *this;
}
bool SpaceVector::operator>=(SpaceVector rhs) const {
	return !(*this > rhs);
}
bool SpaceVector::operator<=(SpaceVector rhs) const {
	return !(*this > rhs);
}

SpaceVector SpaceVector::operator-() const {
	return SpaceVector(-x, -y, -z);
}

double SpaceVector::magnitude() const {
	return sqrt(squared());
}
SpaceVector SpaceVector::unit() const {
	return *this / magnitude();
}
double SpaceVector::squared() const {
	return x * x + y * y + z * z;
}

double SpaceVector::getX() const {
	return x;
}
double SpaceVector::getY() const {
	return y;
}
double SpaceVector::getZ() const {
	return z;
}
