#pragma once
#include "glm/glm.hpp"
class ColorDbl
{
private:
	glm::vec3 values;

public:
	ColorDbl();
	ColorDbl(double inR, double inG, double inB);
	ColorDbl(glm::vec3 inVec);
	glm::vec3 GetValues();
};

