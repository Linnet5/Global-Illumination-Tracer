#pragma once
#include "Triangle.h"
#include "Shapes.h"
#include "LightSource.h"
class Scene
{
public:
	LightSource lightList[1];
	Triangle room[24];
	Triangle lightSource[2];
	float EPSILON = 0.0001f;
	Vertex vertexList[14] = { Vertex(5,0,5), Vertex(10,6,5), Vertex(13,0,5), Vertex(10,-6,5), Vertex(0,-6,5), Vertex(-3,0,5), Vertex(0,6,5), 
							Vertex(5,0,-5), Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5), Vertex(0,-6,-5), Vertex(-3,0,-5), Vertex(0,6,-5)};
	Vertex lightVertex[4] = { Vertex(3.5, 2.5, 5-EPSILON), Vertex(3.5, 5.5, 5-EPSILON), Vertex(6.5, 2.5, 5-EPSILON), Vertex(6.5, 5.5, 5-EPSILON) };
	Shapes** objects = new Shapes*[10];

	Scene();
};
