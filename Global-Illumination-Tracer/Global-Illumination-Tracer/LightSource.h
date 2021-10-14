#pragma once
#include "Triangle.h"
#include "Ray.h"
class LightSource
{

//Light source defined by two triangle objects.
public:
	Triangle tris[2];
	glm::vec3 edge1;
	glm::vec3 edge2;
	double intensity;

	LightSource();
	LightSource(Vertex v0, Vertex v1, Vertex v2, Vertex v3, double inIntensity);
	bool renderFunction(Ray& renderRay, glm::vec3 direction);
};

