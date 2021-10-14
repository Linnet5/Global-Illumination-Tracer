#pragma once
#include "Shapes.h"
#include "Triangle.h"

class Tetrahedron : public Shapes{
public:
	Triangle sides[4];
	float size = 2;
	glm::vec3 center = glm::vec3(4.0f, 1.0f,-2.0f);
	Vertex vertexList[4];
	
	
	bool renderFunction(Ray& renderRay, glm::vec3 direction);
	Tetrahedron();
};