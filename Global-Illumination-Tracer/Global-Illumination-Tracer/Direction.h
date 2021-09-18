#pragma once
#include "Vec3.h"
class Direction
{
private:
	Vec3 direction;

public:
	Direction();
	Direction(double inX, double inY, double inZ);
	Direction(Vec3 inVec);
};

