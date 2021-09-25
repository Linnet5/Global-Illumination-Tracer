#pragma once
#include "Ray.h"

class Shapes
{
public:
	virtual bool renderFunction(Ray& renderRay, Vec3 direction) = 0;
};

