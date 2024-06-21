#pragma once
#include "SpaceVector.h"
#include "SculptureData.h"

struct TriscelData : SculptureData {
	TriscelData(const SpaceVector& a, const SpaceVector& b, const SpaceVector& c) :
		normal((a - c) / (b - c)), planeConstant(c * normal), A(a - c), B(b - c), bPrime((B - (A * (B * A) / A.squared()))) {};
	const SpaceVector& normal;
	const double& planeConstant;
	const SpaceVector& A; 
	const SpaceVector& B;
	const SpaceVector& bPrime;
};
