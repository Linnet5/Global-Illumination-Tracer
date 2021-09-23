#pragma once
#include "Vec3.h"
#include "Triangle.h"
#include "ColorDbl.h"
class Ray
{
public:
	Vec3 start;
	Vec3 end;
	Triangle* endPointTriangle;
	ColorDbl color;
	Ray(const Vec3& inStart, const Vec3& inEnd, ColorDbl inColor);
	void setTriangle(Triangle* triangle);
};

