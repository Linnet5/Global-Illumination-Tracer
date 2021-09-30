#include "Ray.h"

Ray::Ray(const glm::vec3& inStart, const glm::vec3& inEnd, ColorDbl inColor)
{
	start = inStart;
	end = inEnd;
	color = inColor;
	endPointTriangle = nullptr; //yikes
}

void Ray::setTriangle(Triangle* triangle){
	endPointTriangle = triangle;
}

