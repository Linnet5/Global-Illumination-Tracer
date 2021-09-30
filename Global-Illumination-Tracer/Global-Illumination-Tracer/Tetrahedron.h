#pragma once
#include "Shapes.h"
#include "Triangle.h"

class Tetrahedron : public Shapes{
public:
	Triangle sides[4];
	Vertex vertexList[4] = {Vertex(3, 1, 1), Vertex(3, -1, -1), Vertex(1, 1, -1), Vertex(1,-1, 1)};

	bool renderFunction(Ray& renderRay, glm::vec3 direction);
	Tetrahedron();
};