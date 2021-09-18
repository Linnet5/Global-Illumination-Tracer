#pragma once
#include "Vec3.h"
class ColorDbl
{
private:
	Vec3 values;

public:
	ColorDbl();
	ColorDbl(double inR, double inG, double inB);
	ColorDbl(Vec3 inVec);
};

