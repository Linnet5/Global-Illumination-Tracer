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

	ColorDbl color;
	Direction dir;

	//Functions
	Direction calculateNormal();


public:
	Triangle();
	Triangle(Vertex inV0, Vertex inV1, Vertex inV2, ColorDbl inColor);
	bool mollerTrumbore(Vec3 rayOrigin, Vec3 rayDirection, Vec3& intersectionPoint);
};


