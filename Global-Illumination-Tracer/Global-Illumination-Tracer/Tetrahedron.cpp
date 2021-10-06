#include "Tetrahedron.h"
#include <iostream>

Tetrahedron::Tetrahedron() {
	sides[0] = Triangle(vertexList[0], vertexList[2], vertexList[1], ColorDbl(227, 242, 160));
	sides[3] = Triangle(vertexList[0], vertexList[2], vertexList[3], ColorDbl(227 * 0.8, 242 * 0.8, 160 * 0.8)); //RUBEN S�GER ATT JAG SKA KOMENTERA DET H�R �R FRONT 
	sides[1] = Triangle(vertexList[0], vertexList[3], vertexList[1], ColorDbl(227 * 0.6, 242 * 0.6, 160 * 0.6));
	sides[2] = Triangle(vertexList[1], vertexList[2], vertexList[3], ColorDbl(227 * 0.4, 242 * 0.4, 160 * 0.4));  //ordningen spelar roll, vi f�r wired intersections / en bakre triangle skriver �ver.
} 

bool Tetrahedron::renderFunction (Ray& renderRay, glm::vec3 direction)
{
	glm::vec3 t = glm::vec3(999.0f, 999.0f, 999.0f);
	bool flag = false;
	for (int tri = 0; tri < 4; tri++) {
		if(sides[tri].mollerTrumbore(renderRay.start, direction, renderRay.end)){
			if(glm::length(renderRay.end) < glm::length(t)){
				renderRay.endPointTriangle = &sides[tri];
				t = renderRay.end; //fel ingetligen men f�r kanske fixa sen
				flag = true;
			}
		}
	}
	return flag;
}
