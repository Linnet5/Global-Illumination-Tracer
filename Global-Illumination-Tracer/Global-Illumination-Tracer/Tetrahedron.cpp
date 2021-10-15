#include "Tetrahedron.h"
#include <iostream>

Tetrahedron::Tetrahedron() {
	vertexList[0] = Vertex(center + glm::vec3(0, 0, size / 2)); //top
	vertexList[1] = Vertex(center + glm::vec3(-size / 2, 0, -size / 2)); //facing camera
	vertexList[2] = Vertex(center + glm::vec3(size / 2, size / 2, -size / 2)); //back left
	vertexList[3] = Vertex(center + glm::vec3(size / 2, -size / 2, -size / 2)); //back right

	sides[0] = Triangle(vertexList[1], vertexList[3], vertexList[2], ColorDbl(227, 242, 160), Material(0.5)); 
	sides[3] = Triangle(vertexList[1], vertexList[0], vertexList[2], ColorDbl(227, 242, 160), Material(0.5));  
	sides[1] = Triangle(vertexList[1], vertexList[0], vertexList[3], ColorDbl(227, 242, 160), Material(0.5));
	sides[2] = Triangle(vertexList[0], vertexList[3], vertexList[2], ColorDbl(227, 242, 160), Material(0.5));  
} 

bool Tetrahedron::renderFunction (Ray& renderRay, glm::vec3 direction)
{
	
	bool flag = false;
	for (int tri = 0; tri < 4; tri++) {
		if(sides[tri].mollerTrumbore(renderRay.start, direction, renderRay.end, renderRay.tDistance)){
			renderRay.endPointTriangle = &sides[tri];
			renderRay.endPointSphere = false;
			flag = true;
			}
		}
	return flag;
}
