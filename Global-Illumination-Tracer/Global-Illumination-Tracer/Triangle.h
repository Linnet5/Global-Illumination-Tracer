#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"

class Triangle
{
private:
	//Vars
	Vertex v1;
	Vertex v2;
	Vertex v3;

	ColorDbl color;
	Direction dir;

	//Functions
	Direction calculateNormal();


public:
	Triangle();
	Triangle(Vertex inV1, Vertex inV2, Vertex inV3, ColorDbl inColor);
};


