#pragma once
#include "SpaceVector.h"

class PlascelData {
public:
	PlascelData(const SpaceVector& origin, const SpaceVector& xaxis, const SpaceVector& yaxis) :
		normal((yaxis - origin) / (xaxis - origin)),
		planeConstant(origin * normal), 
		yArm(yaxis - origin),
		xArm(xaxis - origin),
		xPrime((xArm - (yArm * (xArm * yArm) / yArm.squared()))) {};
	const SpaceVector normal;
	const double planeConstant;
	const SpaceVector yArm;
	const SpaceVector xArm;
	const SpaceVector xPrime;
};