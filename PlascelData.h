#pragma once
#include "SpaceVector.h"

// Contains extra calculated values that are repeated throughout rendering
struct PlascelData {
public:
	PlascelData(const SpaceVector& origin, const SpaceVector& xaxis, const SpaceVector& yaxis) :
		normal((yaxis - origin) / (xaxis - origin)),
		planeConstant(origin * normal), 
		yArm(yaxis - origin),
		xArm(xaxis - origin),
		xPrime((xArm - (yArm * (xArm * yArm) / yArm.squared()))),
		xPrimeSquaredReciprocal(1.0 / xPrime.squared()),
		yArmSquaredReciprocal(1.0 / yArm.squared())
	{};
	// The normal vector of the plane
	const SpaceVector normal;

	// Constant in plane equation that determines it position
	// origin * normal
	const double planeConstant;

	// The displacement from the origin to yaxis
	// yaxis - origin
	const SpaceVector yArm;

	// The displacement from the origin to xaxis
	// xaxis - origin
	const SpaceVector xArm;

	// The portion of the xArm that is perpendicular to the yArm
	const SpaceVector xPrime;

	// 1 / (xPrime*xPrime) 
	// Saves doing extra multiplication and division
	const double xPrimeSquaredReciprocal;
	// 1 / (yArm*xPrime) 
	// Saves doing extra multiplication and division
	const double yArmSquaredReciprocal;
};