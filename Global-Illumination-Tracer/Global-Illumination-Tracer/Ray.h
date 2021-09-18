#pragma once
#include "Vertex.h"
#include "Triangle.h"
#include "ColorDbl.h"
class Ray
{
private:
	Vertex start;
	Vertex end;
	Triangle* endPointTriangle;
	ColorDbl color;
public:
	Ray(const Vertex& inStart, const Vertex& inEnd, ColorDbl inColor);
	void setTriangle(Triangle* triangle);
};

