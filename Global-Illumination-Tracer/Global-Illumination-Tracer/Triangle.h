#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
#include "Material.h"


class Triangle
{
private:
	//Vars
	Vertex v0;
	Vertex v1;
	Vertex v2;

	glm::vec3 dir;

public:
	//float reflectance = 0.5;
	Material material;
	ColorDbl color;
	Triangle();
	Triangle(Vertex inV0, Vertex inV1, Vertex inV2, ColorDbl inColor, Material inMaterial);
	bool mollerTrumbore(glm::vec3 start, glm::vec3 rayDirection, glm::vec3& intersectionPoint, float& inT);
	glm::vec3 calculateNormal();
	Vertex getVertex(int vertexIndex);
};


