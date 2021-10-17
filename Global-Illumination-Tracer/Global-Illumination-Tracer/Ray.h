#pragma once
#include "Triangle.h"
#include "ColorDbl.h"
#include "glm/glm.hpp"

class Sphere;

class Ray
{
public:
	glm::vec3 start;
	glm::vec3 end;
	Triangle* endPointTriangle;
	Sphere* endPointSphere;

	/*
	//Sphere representation
	bool endPointSphere;
	float radius;
	float sphereReflectance;
	glm::vec3 center;
	ColorDbl sphereColor;
	*/

	ColorDbl color;
	float tDistance;
	Ray(const glm::vec3& inStart, const glm::vec3& inEnd, ColorDbl inColor);
	void setTriangle(Triangle* triangle);
};

