#pragma once
#include "Triangle.h"
class Scene
{
public:
	Triangle room[24];
	Vertex vertexList[14] = { Vertex(5,0,5), Vertex(10,6,5), Vertex(13,0,5), Vertex(10,-6,5), Vertex(0,-6,5), Vertex(-3,0,5), Vertex(0,6,5), 
							Vertex(5,0,-5), Vertex(10,6,-5), Vertex(13,0,-5), Vertex(10,-6,-5), Vertex(0,-6,-5), Vertex(-3,0,-5), Vertex(0,6,-5)};
	Scene();
};
