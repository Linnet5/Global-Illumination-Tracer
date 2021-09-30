#pragma once
#include "Ray.h"

class Shapes
{
public:
	virtual bool renderFunction(Ray& renderRay, glm::vec3 direction) = 0;
};

