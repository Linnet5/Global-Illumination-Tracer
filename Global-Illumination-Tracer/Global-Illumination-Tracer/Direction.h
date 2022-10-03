#pragma once
#include "glm/glm.hpp"

class Direction
{
private:
	glm::vec3 direction;

public:
	Direction();
	Direction(double inX, double inY, double inZ);
	Direction(glm::vec3 inVec);
};

