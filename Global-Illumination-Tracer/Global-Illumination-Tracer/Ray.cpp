#include "Ray.h"

Ray::Ray(const glm::vec3& inStart, const glm::vec3& inEnd, ColorDbl inColor)
{
	start = inStart;
	end = inEnd;
	color = inColor;
	endPointTriangle = nullptr;
	endPointSphere = false;
	center = glm::vec3(0.0f, 0.0f, 0.0f);
	radius = 0.0f;
	sphereColor = ColorDbl(0.0f, 0.0f, 0.0f);
	sphereReflectance = 0.0f;
	tDistance = 999.0f;
}

void Ray::setTriangle(Triangle* triangle){
	endPointTriangle = triangle;
}

