#pragma once
#include "Shapes.h"
#include "Triangle.h"

class Tetrahedron : public Shapes{
public:
	Triangle sides[4];
	float size = 1;
	glm::vec3 center = glm::vec3(5.0f, 4.0f,-3.0f);
	Vertex vertexList[4];
	
	
	bool renderFunction(Ray& renderRay, glm::vec3 direction);
	Tetrahedron();
};