#include "Ray.h"

Ray::Ray(const Vec3& inStart, const Vec3& inEnd, ColorDbl inColor) {
	start = inStart;
	end = inEnd;
	color = inColor;
	endPointTriangle = nullptr; //yikes
}

void Ray::setTriangle(Triangle* triangle){
	endPointTriangle = triangle;
}

