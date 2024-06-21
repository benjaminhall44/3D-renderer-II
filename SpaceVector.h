#pragma once

class SpaceVector {

public:
	double x, y, z;
	SpaceVector() : x(0), y(0), z(0) {}
	SpaceVector(double x, double y, double z) : x(x), y(y), z(z) {}
	// Vector addition
	SpaceVector operator+(SpaceVector) const;
	SpaceVector& operator+=(SpaceVector);
	SpaceVector operator-(SpaceVector) const;
	SpaceVector& operator-=(SpaceVector);
	// Vector-scalar multiplication
	SpaceVector operator*(double) const;
	SpaceVector& operator*=(double);
	SpaceVector operator/(double) const;
	SpaceVector& operator/=(double);
	// Vector dot product
	double operator*(SpaceVector) const;
	// Vector cross product
	SpaceVector operator/(SpaceVector) const;
	SpaceVector& operator/=(SpaceVector);

	bool operator==(SpaceVector) const;
	bool operator>(SpaceVector) const;
	bool operator<(SpaceVector) const;
	bool operator>=(SpaceVector) const;
	bool operator<=(SpaceVector) const;

	SpaceVector operator-() const;

	double magnitude() const;
	SpaceVector unit() const;
	double squared() const;

	double getX() const;
	double getY() const;
	double getZ() const;

};

const SpaceVector ZEROVECTOR(0, 0, 0);
const SpaceVector IVECTOR(1, 0, 0);
const SpaceVector JVECTOR(0, 1, 0);
const SpaceVector KVECTOR(0, 0, 1);
