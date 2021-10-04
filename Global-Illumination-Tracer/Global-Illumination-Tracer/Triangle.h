#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"

class Triangle
{
private:
	//Vars
	Vertex v0;
	Vertex v1;
	Vertex v2;

	glm::vec3 dir;

	


public:
	float reflectance = 0.18; 
	ColorDbl color;
	Triangle();
	Triangle(Vertex inV0, Vertex inV1, Vertex inV2, ColorDbl inColor);
	bool mollerTrumbore(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& intersectionPoint);
	glm::vec3 calculateNormal();
};


