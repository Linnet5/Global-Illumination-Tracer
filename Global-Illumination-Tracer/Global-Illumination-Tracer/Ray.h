#pragma once
#include "Triangle.h"
#include "ColorDbl.h"
#include "glm/glm.hpp"

class Ray
{
public:
	glm::vec3 start;
	glm::vec3 end;
	Triangle* endPointTriangle;
	ColorDbl color;
	Ray(const glm::vec3& inStart, const glm::vec3& inEnd, ColorDbl inColor);
	void setTriangle(Triangle* triangle);
};

